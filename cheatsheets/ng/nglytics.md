# Analytics in Angular

## Listen to router events (& forward to Google Analytics (GA))
(after inserting the ga/gtag script into index.html)
```ts
declare var gtag: any;

export class AppCmp {
    constructor(router: Router) {
        const navEndEvents = router.events.pipe(filter(event => event instanceof NavigationEnd);
        navEndEvents.subscribe((event: Navigationend) => {
            gtag('config','UA-99336633-9', {
                'page_path': event.urlAfterRedirects
            });
        });
    }
}
```

## angulartics2 
> $ npm install angulartics2 --save         # docu: https://github.com/angulartics/angulartics2
### Features:
1. directives: angulartics2On, angularticsAction, angularticsCategory, angularticsLabel, angularticsValue, angularticsProperties
1. API:
    1. import { Angulartics2GoogleAnalytics } from 'angulartics2/ga';
    1. import { Angulartics2 } from 'angulartics2';
    1. import { Angulartics2RouterlessModule } from 'angulartics2/routerlessmodule';
    1. Angulartics2Module.forRoot({ pageTracking: { clearIds: true, excludedRoutes: [ ...
    1. angulartics2GoogleAnalytics.startTracking();
    1. this.angulartics2.eventTrack.next({  action: 'myAction', properties: {  category: 'myCategory', label: 'myLabel', }, });
1. supports all the main web analytics tools like GA or piwik (see https://github.com/angulartics/angulartics2#supported-providers )



## Listen to webpage-hash change with plain JS
(see also https://developer.matomo.org/guides/spa-tracking )<br>
(after configuring a new Tag in matomo incl. tracking type)<br>
(after inserting the matomo tag manager script into index.html)<br>
(use the Matomo preview mode (/?mtmPreviewMode={hash}) **or** the Matomo-Dashboard/Visitors/Visit-Log to see the sent infos)<br>

```js
window.addEventListener('hashchange', function() {
    _paq.push(['setCustomerUrl','/'+window.location.hash.substr(1)]);
    _paq.push(['setDocumentTitle', 'My New Title']);
    _paq.push(['trackPageView']);
});
```
<img src=mtmPreviewMode.png width="550px">

# PIWIK Setup on Windows
1. download & unpack matomo.zip (a pure php web-app)
1. download & unpack nginx-1.17.0.zip (for windows)
1. download & unpack php-7.3.6-nts-Win32-VC15-x64.zip
    1. create '[start-php-fcgi.bat](piwik/start-php-fcgi.bat)':
        1. set PATH=%~dp0.\php;%PATH%
        1. %~dp0.\php\php-cgi.exe -b 127.0.0.1:9123
1. edit [nginx.conf](piwik/nginx.conf) (eg. based on https://github.com/matomo-org/matomo-nginx) , with fast-cgi config:
    1. fastcgi_pass   127.0.0.1:9123;
1. create [%PHPDIR%/php.ini](piwik/php.ini) with
    1. extension=ext/php_mysqli.dll
    1. extension=ext/php_pdo_mysql.dll
    1. extension=ext/php_mbstring.dll
    1. mbstring.language = German
1. create MySQL database & DB-user & set the access rights
1. start start-php-fcgi.bat & nginx.exe -> localhost/index.php -> follow setup steps...

## PIWIK UI
<img src=piwik/ui.1.png width="550px"><img src=piwik/ui.2.png width="550px"><img src=piwik/ui.3.png width="550px"><img src=piwik/ui.4.png width="550px"><img src=piwik/ui.5.png width="550px"><img src=piwik/ui.6.png width="550px">

## Launching dockerized Matomo:
Launching dockerized Matomo with external MariaDB database and locally mapped persistent data (for saved matomo configuration)
<img src=dockerizedmatomo/dockerizedmatomo.png width="750px">

### Would you like to access Matomo running in a VM?
1. choose a free port in virtualmatomo.sh (instead of 8080, eg. 8765)
2. edit ./virtualmatomo/matomo/config/config.ini : trusted host's port should be the same
3. in VirtualBox, set up a network -> port forwarding rule (with the same port in guest and on host)
4. from now on, you will be able to access localhost:8765 on your host!
5. after launched the matomo server within the VM as a docker container, look at the logs to see the activity within the running container:
    > $ sudo docker ps
    
    > $ sudo docker logs -f [containerid]

### Troubles getting traffic saved?
With the default settings, browsers sends nowadays the do-not-track command and matomo (again, with default settings) won't save then the traffic from these users.
<img src=do.not.track.png width="550px">
