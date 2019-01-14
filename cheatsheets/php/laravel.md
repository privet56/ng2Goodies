# Laravel Events and Listener
```php
php artisan make:auth
```

...creates controller, view, ...
## app/Http/Controllers/Auth/RegisterController.php
**Without Events**
```php
<?php
namespace App\Http\Controllers\Auth;
//use ...
class RegisterController extends Controller
{
    //...validators, etc

    protected function craete(array $data)
    {
        $u = User::create([
            'name' => $data['name'],
            'mail' => $data['mail'],
            'pwd' => bcrypt($data['pwd']),
        ]);

        $this->sendActiCodeTo($u)->assignRoleTo($u);

        return $u;
    }
    protected sendActiCodeTo($u) {
        \Log::info('act', ['user' => $u]);
        return $this;
    }
    protected assignRoleTo($u) {
        //...
        return $this;
    }
}
```
## With Events
### app/Providers/EventServiceProvider.php
```php
<?php
//...
    protected $listen = [
        'App\Events\UserRegisteredEvent' => [ 'App\Listeners\SendActiCodeListener','App\Listeners\AssignRoleListener' ],
    ];

```
### create Listener Class
> $ php artisan event:generate      # generates *Event-/*Listener classes from the listen array!
#### Edit app/Events/UserRegisteredEvent.php:
```php
<?php
namespace App\Events;
//use...
class UserRegisteredEvent
{
    use Dispatchable, InteractsWithSockets, SerializesModels;
    public $user;

    public function __construct(User $user)
    {
        this->user = $user;
    }
}
```
#### Edit app/Listeners/SendActiCodeListener.php:
```php
<?php
namespace App\Listeners;
//use...
class SendActiCodeListener
{
    public function __construct()
    {

    }
    public function handle(UserRegisteredEvent $event)
    {
        //handle event it with $event->user
        //dd($event);   //die-and-dump
    }
}
```
#### app/Http/Controllers/Auth/RegisterController.php : fire the event!
(instead of the explicit function call to sendActiCode)
```php
event(new UserRegisteredEvent($u));
```

# Form Request Validation
Blade is the template engine!
> $ php artisan make controller FormController

> $ php artisan make make:request MyFormValidation  # creates Http/Request/MyFormValidation.php

## HTML resources/views/form.blade.php
```html
<form action="form">
    {{ csrf_field() }}
    @if(count($errors) > 0)
        @foreach($errors->all() as $e)
            {{ $e }}
    @endif
    <input name="name">

</form>
```
## Route
### add in web.php
```php
Route::get('my','formController@index')->name('form');
Route::post('my','formController@store')
```
### app\Http\Controllers\FormController.php
```php
    //...
    use App\Http\Request\MyFormValidation;

    public function index()
    {
        return view('form');
    }
    //this is the 'traditional' way...
    public function store(request $request)
    {
        this->validate($request[
            'name'=>'required|max:20',
        ]);

        //...
        return $request->all();
    }
    //this is the 'better' way...
    public function store(MyFormValidation $request)
    {
        //vali already done! :-)
        //...
    }

```
### Http/Request/MyFormValidation.php
```php
    //...
    public function rules()
    {
        return [
            'name'=>'required|max:20',
        ];   
    }
    public function messages()
    {
        return ['name.required' => 'The Name field is required', ];//do it also for name.max
    }
    public function authorize() { return true; }
```
# Invisible reCAPTCHA

Register on https://www.google.com/recaptcha/admin (choose invisible recaptcha)

> $ composer require albertcht/invisible-recaptcha

### app/config/app.php : add ServiceProvider to 'providers' array
AlbertCht\InvisibleReCaptcha\InvisibleReCaptchaServiceProvider::class

### .env
```sh
INVISIBLE_RECAPTCHA_SITEKEY={sitekey}
INVISIBLE_RECAPTCHA_SECRETKEY={secretkey}
INVISIBLE_RECAPTCHA_BADGEHIDE=false
INVISIBLE_RECAPTCHA_DEBUG=false
```
### web.php
```php
Route::get('my','formController@index')->name('form');
Route::post('my','formController@store')
```
### resources\form.blade.html
```html
<form>
    {{ csrf_field() }}
    <input name=name><input type=submit>
    @captcha()
</form>
```
### app\Http\Controllers\FormController.php
```php
    //...
    public function store(request $r)
    {
        $this->validate($r, [
            'g-recaptcha-response' => 'required|captcha'
        ]);

        return $request->all();
    }
```

# Laravel Scout: a Search Service by Algolia
requires account on www.algolia.com, search index will be on their server (batch upload is also supported)

> $ composer require laravel/scout

> $ composer require algolia/algoliasearch-laravel

## config/app.php : 'providers'
Laravel\Scout\ScoutServiceProvider::class,
AlgoliaSearch\Laravel\AlgoliaSearchServiceProvider::class,
### Create a ServiceProvider
> $ php artisan vendor:publish --provider="Laravel\Scout\ScoutServiceProvider"

> $ php artisan vendor:publish

> $ composer require algolia/algoliasearch-client.php

creates config/scout.php

Set here your algolia app key & secret

### app\User.php
```php
    //...
    use Laravel\Scout\Searchable;
    class User extends Authenticatable
    {
        use Searchable;
    }
    public function searchableAs() {
        return 'name';
    }
    //no code necessary to feed the online search-index
```
### Search!

**Route**: web.php
```php
Route::get('/search/{searchkey}', 'SearchController@search');
```

#### resources\views\search.blade.html
```html
<link rel="stylesheet" href="{{ asset('css/app.css') }}">
@foreach($users as $u)
 {{ $u->name }}
@endforeach
```
#### 
```php
public void search($searchkey) {
    $users = App\user::search('searchterm')->get();
    return $users;
    //return view('search',compact('users'));
}
```
# Laravel Mix
    compiles & minimizes assets (js, scss)
    build config: webpack.min.js
    needs node & npm installed. Provides package.json. Call:
```sh
npm install         # use no-bin-links on win or inside a vm
npm run dev|watch|watch-poll|hot|production
```
### Laravel Mix Browsersync reloading
Add in webpack.mix.js
```js
//extend mix.js with new .js files to be compiled
mix.js(['resources/assets/js/app.js','resources/assets/js/my.js'], 'public/js')
    .sass('resources/assets/sass/app.scss','public/css');
mix.browserSync('http://localhost:8000');

```
```sh
php artisan serce   # -> http://localhost:8000  # command window 1
npm run watch       # -> http://localhost:3000  # command window 2 # see changes here on :3000
```

# Laravel Localization
Default config is in app.php (locale & fallback_locale)

**Route**: web.php
```php
Route::get('/locale/{lang?}', function($lang=null) {
    App::setlocale($lang);
    return view('my');
}
```
#### HTML
```html
<div>Current locale: {{ confi('app.locale') }}</div>
<div>Welcome in Portugese: {{ __('header.welcome') }}</div> or:
<div>Welcome in Portugese: @lang('header.welcome')</div>
<div>Welcome in : @lang('header.welcomeat',['name'=>'Portugal'])</div>
<div>Welcome in : {{ trans_choice('header.item', 3) }} </div>
```
### resources\lang\pt\header.php
```php
<?php
    return [
        'welcome' => 'Welcome in Portugal!',
        'welcomeat' => 'Welcome in :name!',
        'item'=>'Item (:count) | Items (:count)',   //singular form | multiple form
        'item_version_2'=>'{0} No Item (:count) | {1} One Item | [2,*] Items (:count)',   //singular form | multiple form
    ];
```
# Custom Commands with the Artisan CLI
```sh
php artisan make:command My # creates app\Console\Commands\My.php
php artisan My reqargu --optargu=o             # run command!
```
**Alternative**: app\Console\Kernel.php::commands = require base_path('routes/console.php');

### app\Console\Commands\My.php
```php
# Edit My.php, set $signature & $description & arguments
$signature = "my:My {requiredargument : my description} {--L|optionalargument=defaultValue}";
public function handle()
{
    $this->info($this->argument('requiredargument') .' '. $this->option('optionalargument'));
    $answer = $this->ask('question');
    $this->error(...);
    $this->secret(...);
    $bConfirm = $this->confirm(...);
    //Table:
    $header = ['col1','Col 2'];
    $u = User::select('name','mail')->get();
    $this->table($header, $u);
    //You can do real action, like alter table:
    DB::statement("ALTER TABLE $myparam1 RENAME TO $myparam2");
}

# in Kernel.php, you have to register your command:
protected $commands = [
    Commands\My::class,
];

# in routes/console.php, do can do this, without registration:
Artisan::command('My', function() { $this->info('info'); })->desribe('description');
```

# Queues
You can use DB-Table, Redis, AWS-SQS etc to hold your queue data
.env
```ini
MAIL_HOST=...
MAIL_PORT=...
...username, pwd,driver...
```
web.php
```php
Route::get('sendEmail', function() {
    Mail::to('my@my.com')->send(new SendEmailMailable());   //takes long!
    return "done!";
});
```
```sh
php artisan make:mail SendEmailMailable     # -> App\Mail\SendEmailMailable.php
php artisan queue:table                     # use DB-table for the queue
php artisan migrate                         # jobs table is created
php artisan make:job SendEmailJob           # app/Jobs/SendEmailJob.php
php artisan queue:work                      # run it in parallel to your 'php artisan serve'
```
.env
```ini
QUEUE_DRIVER=database
```
php code
```php
//config/queue.php
'default' => env('QUEUE_DRIVER', 'sync'),   //overridden by .env

//web.php
Route::get('sendEmail', function() {
    //dispatch(new SendEmailJob());
    $job = (new SendEmailJob())->delay(Carbon::now()->addSeconds(1));
    dispatch($job);
    return "done!";
});

//app/Jobs/SendEmailJob.php
    public function handle()
    {
        Mail::to('my@my.com')->send(new SendEmailMailable());   //takes long, but inside an async job
    }
```

# Broadcasting with Pusher
```sh
composer require pusher/pusher-php-server "~2.6"        #optional online-service for broadcasting (://puhser.com/)
npm install --save laravel-echo pusher-js
```
.env
```ini
BROADCAST_DRIVER=pusher
```
```php
//app.php: add new provider:
    App\Providers\BroadcastSesrviceProvider::class,

//web.php
Route::get('listen2broadcast', function() {
    
    return view("listen2broadcast");
});

//config/broadcasting.php
'connection' => [
        'pusher' => [
            //...
            'options' => [
                'cluster' => 'eu',      //use as stated on the pusher website
                'encrypted'=> true
            ]
        ]
    ]
// app/Events/UserRegisteredEvent.php:
use Illuminate\Contracts\Broadcasting\ShouldBroadcast;
class UserRegisteredEvent implements ShouldBroadcast
{
    //...
    public function broadcastOn()
    {
        return new PrivateChannel('channel-name', "payload");
    }
//routes/channels.php
Broadcast::channel('channel-name', function() {
    return true;//allow to call channel
})
```
app.js
```js
import Echo from 'laravel-echo'
window.Pusher = require('pusher-js');
window.Echo = new Echo({
    broadcaster:'pusher',
    key: 'my-pusher-key'
    cluster:'eu',
    encrypted:true
});
//...
const app = new Vue({
    el:'#app',
    created() {
        //Echo has the channel and private functions
        Echo.(channel|private)('channel-name').listen('UserRegisteredEvent', (e) => {
            console.log(e);
        });
    }
});
```
listen2broadcast.blade.html
```html
<meta name="csrf-token" content="{{ csrf_token() }}">
<script src='{{ asset('js/app.js') }}'></script>

```
# Gates
Gates = Auth extension for authorization

```sh
php artisan make:policy SubsPolicy
php artisan make:policy SubsPolicy --model=Post
```
```html
//home.blade.html
@if Route::has('login'))
    @if(Auth::check())
        <a href="{{ url('/home') }}">Home</a>
        @can('subs_only', Auth::user())
            <a href="{{ url('/subs') }}">Subscribers</a>
        @endcan
    @else
        <a href="{{ url('/login') }}">Login</a>
    @endif
@endif

//resources/views/subs.blade.html
<div>the protected content for subs_only</div>

```
```php
//web.php
Route::get('/subs' function() { 
    if(Gate::allows('subs_only', Auth::user())) {
        return view('subs');
    }
    return "not allowed";
});

//Providers/AuthServiceProvider.php
    //...
    $policies = [
        //...
        User::class => SubsPolicy::class,
    ];
    public function boot()
    {
        $this->registerPolicies();

//beginner version:
        Gate::define('subs_only', function($user) {
            return ($user->subs == 1);
        });
//nice version:
        Gate::define('subs_only', 'App\Policies\SubsPolicy@subs_only');
        //.view , .delete , .post ...
        Gate::define('subs_only.view', 'App\Policies\SubsPolicy@subs_only');
    }
//SubsPolicy.php
    //...
    public function subs_only($user)
    {
        return ($user.subs == 1);
    }
```
