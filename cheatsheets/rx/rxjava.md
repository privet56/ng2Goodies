# RxJava

    Do async work with Rx!
    Rx is a lib for composing asynchronous events
    Rx = Reactive Extensions
    Rx has many flawors: RxJava, RxSwift, RxJs...
    Rx = Observables + LINQ + Schedulers

Async Tools:
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
        subsciber.onNext("");
        subscirber.onCompleted();
        subsciber.onError(...);
    }
}
```
```kotlin
Observable.create<String> { s -> 
    val expensiveThing1 = doExpensiveComputation()
    s.onNext(expensiveThing1)
    val expensiveThing2 = doExpensiveComputation()
    s.onNext(expensiveThing2)
    s.onComplete()
}
```
If you want to receive less often messages from an Observable, use
1. Backpressure
2. Sample
3. Throttle
