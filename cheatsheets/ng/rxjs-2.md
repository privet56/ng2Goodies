# RxJS
#### Basics
```js
var srcNever = Rx.Observable.never();

var src = Rx.Observable.create(function(observer) {
    var id = setTimeout(function() {
        try {
            observer.onNext(42);
            throw 'my error';
            observer.onCompleted();
        }
        catch(e) { observer.onError(e);}
    }, 333);
    //return an unsubscribe function to be executed on unsubscribe
    return function() {clearTimeout(id);}
});
var sub = src.subscribe(
    function(value) {

    },
    function(err) {

    },
    function() {

    }
);
sub.dispose();  //~unsubscribe!
```
#### Compare with Promises
```js
var src = Rx.Observable.fromArray([1,2]);
var src = Rx.Observable.intervall(500).take(6);
src.filter(x => x % 2 === 1)
    .map(x => x + '!')
    .forEach(x => console.log(x));

//Promise is not lazy!:
var promise = new Promise((resolve) => {
    setTimeout(() => resolve(42);}, 333);
});
promise.then(x => console.log(x));  //can NOT be cancelled!

//Observable is lazy: does nothing without subscription!
var observable = Rx.Observable.create((observer) => {
    setTimeout(() => observer.onNext(42);}, 333);
});
var disposable = observable.forEach(x => console.log(x));
disposable.dispose();/*~unsubscribe*/ //can be cancelled!
```
#### Throttled Buffering
```js
val clicks = Rx.Observable.fromEvent(btn, 'click');
//unbuffered:
clicks.scan(0, (s) => s + 1).forEach(x => clicked(x));
//buffered:
var open = Rx.Observable(interval(999);
clicks
    //.buffer(open)
    //.filter(x => x.length > 0)
    .buffer(clicks.throttle(999))
    .scan(0, (s) => s + 1)
    .forEach(x => clicked(x));
```
#### Chain Operators:
```js
var src = Rx.Observable.fromArray([1,2]);
src .filter((x) => { return x % 2 === 0;})
    .map((x) => x+"!")
    .startWith(0)
    .reduce((r,x) => {return r + x;})
    .subscribe((re) => {});
```
#### Toggle Streem On/Off
```js
var src = Rx.Observable.intervall(99).map(() => '.');
var isON = Rx.Observable.fromEvent(checkbox, 'change').map((e) => e.target.checked);
isON.filter(x => x === true)
    .flatMapLatest(() => source.takeUntil(isON))
    subscribe(x => doWhenIsOn(x));
```
#### map vs flatMap
```js
var src = Rx.Observable.intervall(99).take(99).map((x) => x*2);
var src = Rx.Observable.intervall(99).take(99)
    .map((x) => Rx.Observable.timer(99).map((x) => x))
    .subscribe(x/*is an observable!*/ => console.log(x));

var src = Rx.Observable.intervall(99).take(99)
    .map((x) => Rx.Observable.timer(99).map((x) => x))
    .mergeAll()
    .subscribe(x/*observable is unpacked!*/ => console.log(x));

var src = Rx.Observable.intervall(99).take(99)
    .flatMap((x) => Rx.Observable.timer(99).map((x) => x))
    .subscribe(x/*observable is unpacked!*/ => console.log(x));
```
#### Hot or Cold?
```js
//cold
var src = Rx.Observable.intervall(99).take(99).map((x) => x*2);
src.subscribe((i) => console.log(i));   //starts with 1
src.subscribe((i) => console.log(i));   //starts with 1 here too! Cold observable

//hot
var src = Rx.Observable.intervall(99).take(99).map((x) => x*2).publish().refCount();
src.subscribe((i) => console.log(i));   //starts with 1
src.subscribe((i) => console.log(i));   //starts & continues with the current value! Hot observable!

//alternative to .refCount:
var src = Rx.Observable.intervall(99).take(99).map((x) => x*2).publish();
src.connect();

// .publish     = make it a hot observable
// .refCount    = autoConnectWhenObserved
```
#### Reduce!
```js
var src = Rx.Observable.fromArray([1,2]);
src.reduce(function(r, x) => r+x, 0).subscribe((r) => console.log(r));

var src = Rx.Observable.intervall(9999).take(9);
//takes very long because reducer waits until Observable finishes...? (if not finishes -> you never get a result)
src.reduce(function(r, x) => r+x, 0).subscribe((r) => console.log(r));

//works also with infinite Observables
src.scan(0, function(r, x) => r+x).subscribe((r) => console.log(r));
```
#### Error Handling
```js
var {Observable} = Rx;
Observable.of(1,2,3).map(x => {
    throw 'error';
})

.catch(err => Observable.just('go ahead'))          //alternative 1
.onErrorResumeNext(Observable.just('go ahead'))     //alternative 2
.retry(9)                                           //alternative 3
.retryWhen(errs => errs.delay(999).take(5))         //alternative 4: call onComplete after 5 errs!
.retryWhen(errs => errs.delay(999).take(5).concat(Observable.throw('eeerrr')))
                                                    //alternative 5: ^ : throw to onError after 5 atttempts
.subscribe(
    x => 'onNext',
    err => 'onError',
    () => 'onComplete'
);
```
#### Double Click do it yourself (actually, the dblclick event exists...)
```js
var clicks = Rx.Observable.fromEvent(btn, 'click');
var dblClicks = clciks.buffer(() => clicks.throttle(333))
    .map(arr => arr.length)
    .filter(len => len >=== 2);     //this actually notices also tripple clicks...
dbClicks.subscribe(event => { label.textContent = 'dblclick!'; })
dbClicks.throttle(999).subscribe(s => { label.textContent = 'zzz...'; });   //reset dblclick-caused action
```
#### Async Handling
```js
var req = Rx.Observable.just("https://api.github.com/users");   //returns an Array of users!
//alternative 1
req.subscribe(url => {
    var res = Rx.Observable.fromPromise(jQuery.getJSON(url));
    res.subscribe(sRes => { console.log(sRes); });
});

//alternative 2
var res = req.flatMap(url => Rx.Observable.fromPromise(jQuery.getJSON(url)));
res.subscribe(sRes => { console.log(sRes); });

//get random elem of the Array
var randomUser = res.map(listUsers => listUsers[Math.floor(Math.random() * lisusers.length)]);
```

```js
var clicks = Rx.Observable.fromEvent(btn, 'click');
//we need 'startup' to start without first click
var startup =  Rx.Observable.just("https://api.github.com/users");  
var req = clicks.map(ev => {
    var randomOffset = Math.floor(Math.random()*555);
    "https://api.github.com/users?since="+randomOffset;
});
var res = req.merge(startup).flatMap(url => Rx.Observable.fromPromise(jQuery.getJSON(url))).map(listUsers => {
   listUsers[Math.floor(Math.random() * lisusers.length)] 
}).subsribe(randomuser => alert(randomUser));
```
