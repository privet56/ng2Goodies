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


//
(new CURLObservable('https://my.com'))->subscribeCallback(null, function($e) { });

```
