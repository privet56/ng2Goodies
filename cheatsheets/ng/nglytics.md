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
