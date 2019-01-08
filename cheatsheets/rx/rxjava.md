# RxJava

    Do async work with Rx!
    Rx is a lib for composing asynchronous events
    Rx = Reactive Extensions
    Rx has many flawors: RxJava, RxSwift, RxJs...
    Rx = Observables + LINQ + Schedulers
    RxMarbles = resource explaining Rx visually

Old-Style Async Tools:
1. AsyncTask
2. ListenableFuture
3. Event Bus
4. Observable

### AsyncTask:
    used on Android, uses side-effects
```java
private class MyTask extends AsyncTask<ParamsType, ProgressType, ResultType>
{
    protected ResultType doInBackground(ParamsType params) { ... }
    protected void onPostExecute(ResultType result) { ... }
}
new MyTask().execute(params);
```

## Rx advantages:
1. Explicit execution
2. easy thread management
3. easily transformable, composable, chainable, combinable = operators & transforms
4. as few side effects as possible

### Rx = Observables + LINQ + Schedulers

1. Observables = asynchronous data stream
2. Linq = query & combine asynchronous data streams with operators
3. Schedulers manage concurrency

### Observables
    they are streams of data
    they are pull based (caveat: Subjects)
    they can be created, stored, passed around
    they abstract away threading, synchronization, concurrency
    Observables = put data in & get data out
#### put data in Observable:
```java
Observable.just("my");
val a = Array<String> = arrayOf("","");     // this is Kotlin!
Observable.from(a);
Observable.create<String> { s ->            // this is Kotlin!
    s.onNext("")
    s.onCompleted()
};
// here is java:
Observable.create(new OnSubscribe<String>() {
    @Override
    public void call(Subscriber<? super String> subscriber) {
        subscriber.onNext("");
        subscriber.onCompleted();
        subscriber.onError(...);
    }
}
```
```kotlin
Observable.create<String> { s -> 
    val expensiveThing1 = doExpensiveComputation()
    s.onNext(expensiveThing1)
    try {
        val expensiveThing2 = doExpensiveComputation()
        s.onNext(expensiveThing2)        
    }
    catch(e:Error) {
        s.onError(e)    //stream ends in incomplete way
    }
    s.onComplete()  //not called if onError called
}
```
If you want to receive less often messages from an Observable, use
1. Backpressure
2. Sample
3. Throttle

## Linq ~ operators
1. combine data
2. filter/reduce
3. transform
```kotlin
Observable.from([1,2])
.map { num ->
    num +1
}
//output: 2,3

.filter { num ->
    num % 2 == 0
}
//output: 2

Observable.merge(o1, o2)
```

## Schedulers
1. Without Subscribe, nothing happens (almost always)
2. Subscribers take functions to handle next,error,complete
3. use subscribeOn & observeOn to assign to threads
```kotlin
val sub : Subscription = Observable.from(array).subscribe(
    { next ->
        Log.i(TAG, "on $next")
    },
    { error ->
        Log.e(TAG, "on error $error")
    },
    {
        //onCompleted
    }
)
sub.unsubscribe()
```
4. .subscribe returns a Subscription, you can unsubscribe from it

### subscribeOn
1. declare only once, (if sets multiple times, declaration farthest upstream wins (=first))
2. defaults to thread on which observable is created
3. Observable will always kick of execution on this thread, no matter where it's declared

### observeOn
1. declare as many times as needed (but: it is possible to create backpressure issues if using observeOn with fast emitting streams)
2. affects all operations downstream
```kotlin
Observable.from(arrayOfString)
    .doOnNext { next ->
        Log.i(TAG, "on $next on ${Thread.currentThread()}")     //here on main thread
    }.observeOn(Schedulers.io()).map { next ->                  // here switches to another thread
        next.length
    }.subscribe { length ->
        Log.i(TAG, "on $length on ${Thread.currentThread()}")   //here on RxIoScheduler
    }

Observable.from(arrayOfString)
    .doOnNext { next ->
        Log.i(TAG, "on $next on ${Thread.currentThread()}")     //here on RxComputationScheduler
    }.observeOn(Schedulers.io()).map { next ->
        next.length
    }.subscribeOn(Schedulers.computation())
    }.subscribe { length ->
        Log.i(TAG, "on $length on ${Thread.currentThread()}")   //here on RxIoScheduler
    }
```
## Usage of Rx
1. bind to clicks & filter them
2. flatmap cache hit with network call
3. handle auth flow with a single stream
4. Examples:
```kotlin
fun Button.debounce(length: Long, unit:TimeUnit) {
    setEnabled(false)
    Observable.timer(length, unit)
        .observeOn(AndroidSchedulers.mainThread())
        .subscribe {
            setEnabled(true)
        }
}

//get size of 24 most recent db photos
fun size(): Observable<Int> = Database.with(ctx)
    .load(DBType.photoDetails)
    .orderByTs(Database.SORT_ORDER.DESC)
    .limit(24)
    .map { it.size() }

return Observable.create<Unit> { s ->
    val outputFile = writeOutputFile(mediaFile)
    when(type) {
        Type.Photo -> addPicToGallery(ctx, outputFile)
        Type.Video -> addVidToGallery(ctx, outputFile)
        else -> {
            s.onError(Error("unknown type"))
        }
    }
    s.onNext(Unit)
    s.onCompleted()
}.subscribeOn(Schedulers.io())

//lift data from localbroadcast
fun codeObservable(): Observable<String?> {
    val filter = IntentFilter(SmsUtility.INTENT_VERIF_CODE)
    return ContentObservable.fromLocalBroadcast(this, filter)
        .map { intent ->
            intent.getStringExtra(SmsUtility.KEY_VERIF_CODE)
        }
}

//onboarding flow
timedAuthObservable.observeOn(Schedulers.io())
    .flatmap { code ->
        userModel.sendVerifyResponse(code)
    }.flatmap {
        userModel.getSuggusername().onErrorReturn { "" }
    }.observeOn(AndroidSchedulers.mainThread())
    .subscribe({ suggestedUserName ->
        //update UI with suggested name
    })

//fetch once verified
override fun getVerifiedData(code: String): Observable<Unit> {
    //verify with backend, then prepare data for ui
    return UserService.noAuthClient
        .verifyUser(authToken, code)
        .flatMap {
            UserService.authClient.fetchUserDetails()
        }.map { data ->
            loadableUserState.loadFromData(data)
        }.observeOn(AndroidSchedulers.mainThread())
}
```
