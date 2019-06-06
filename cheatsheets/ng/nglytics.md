# Analytics in Angular

### Listen to router events (& forward to Google Analytics (GA))
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
### Listen to webpage-hash change with plain JS
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
