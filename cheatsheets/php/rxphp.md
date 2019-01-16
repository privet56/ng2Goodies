# RxPHP
    https://github.com/ReactiveX/RxPHP
```sh
php composer.phar init  # generates composer.json
    # dependency: reactivex/rxphp
    # composer.json contains name, require, "autoload": { "files": ["bootstrap.php"] }
php composer.phar install
    # into /vendor/
    # incl /vendor/autoload.php
```
```php
<?php
require_once __DIR__ . '/vendor/autoload.php';
$a = ['a','b'];
$observer = new \Rx\Observer\CallbackObserver(function($val) {
    printf("%s\n", $val);
}, null/*onError*/, function() {print("completed");} )

\Rx\Observable::fromArray($a)->map(funtion($val) { return strlen($val); })->subscribe($observer);
```
```php
//the default RxPHP implementations is this:
function subscribe(ObserverI $obs, $scheduler = null) {
    $this->observers[] = $obs;
    $this->started = true;
    return new CallbackDisposable(function() use ($obs) {
        $this->removeObserver($obs);
    });
}
```
```php
require_once __DIR__ . '/vendor/autoload.php';
use Rx\Observable;
use Rx\Scheduler;
use Rx\Scheduler\EventLoopScheduler;
use Rx\EventLoop\StreamSelectLoop;
use Rx\Observable\ConnectableObservable;

$l = new StreamSelectLoop();
$s = $bDefaultScheduler = Scheduler::getDefault() : new EventLoopScheduler($l);
$disposable = Observable::range(1, 5, $s)
    ->subscribe(function($v) use (&$disposable) {
        echo "$v\n";
        $disposable->dispose();//=unsubscribe
    });


// ConnectableObservable = takes another Observable as arg
$connObs = new ConnectableObservable(new RangeObservable(0,6, Scheduler::getImmediate()));
$filteredObs = $connObs->map(function($v) { return $v ** 2; })->filter(function($v) { return $v % 2; });
$disposable1 = $filteredObs->subscribe(function($v) { echo "${v}"; });//subscribe an observer
$disposable2 = $filteredObs->subscribe(function($v) { echo "${v}"; });//subscribe another observer
$connObs->connect();


//Subject
$subject = new Subject();
$source = new RangeObservable(0, 6, Scheduler::getImmediate());
$filteredObs = $source->map(function($v) { return $v ** 2; })->filter(function($v) { return $v % 2; });
$disposable1 = $subject->subscribe(function($v) { echo "${v}"; });
$disposable2 = $subject->subscribe(function($v) { echo "${v}"; });
$filteredObs->subscribe($subject);

//retry:
//version without retry:
(new CURLObservable('https://my.com'))->subscribeCallback(null, function($e) { });
//version with retry:
(new CURLObservable('https://my.com'))->retry(3)->subscribeCallback(null, function($e) { });
//advanced retry:
$count = 0;
\Rx\Observable::range(1,6)
    ->map(function() use (&$count) {
        if(++$count == 3) {
            throw new \Exception('err msg');
        }
        return $count;
    })
    ->retry(3)
    ->takeWhile(function($v) {
        return $v <= 6;
    })
    ->subscribe(new MySubject());
//advanced retry:
Observable::defer(function() {
    return new CurlObservable('https://my.com');
})->retry(3)->subscribe(new MySubject());
//better retry = retryWhen:
(new CURLObservable('https://my.com'))
    ->retryWhen(function(Observable $errObs) {
        $notificationObs = $errObs->delay(1111, Scheduler::getDefault())->map(function() { /*onNext*/ return true; });
        return $notificationObs;
    })->subscribe(new MySubject());
//retryWhen - version 2: here no onError will be thrown, but onCompleted (after 3 tries)
(new CURLObservable('https://my.com'))
    ->retryWhen(function(Observable $errObs) {
        $i = 1;
        $notificationObs = $errObs->delay(1111, Scheduler::getDefault())->map(fucntion(Exception $e) use (&$i) {
            $i++;
            return $e;
        })->take(3);
        return $notificationObs;
    })->subscribe(new MySubject());

//catchError
\Rx\Observable::range(1, 6)->map(function($v) {
    if($v == 3) { throw new \Exception(); } return $v;
})->catchError(function(Exception $e, \Rx\Observable $sourceObs) {
    return \Rx\Observable::just(42);
})->subscribe(new MySubject()); //sequence: 1, 2, 42, onCompleted

//testing

//dOn* = doOnNext(callable), doOnError(callable), doOnCompleted(callable), onOnEach(instance)
    //the perform side effect without subscription
Observable::create(function(ObserverInterface $obs) {
    $obs-onNext(1);
    $obs-onNext(2);
    $obs-onError(new \Exception("e"));
}->doOnError(function \Exception $e) {
    //...
})->subscribe(function($v) {}, function( {});
```
