# RxJS
Ng versions >= 6 use RxJS version >= 6. With older RxJS versions, can use *rxjs-compat*.

## Subject
```js
import { Subject } from 'rxjs/Subject';
export class MyService {
    aChange = new Subject<boolean>();
    myFunc() {
        this.aChange.next(true);
    }
}
// usage:
import { Subscription } from 'rxjs/Subscription';
export class MyComp {
    ngOnInit() {
        this.subscription = this.myService.aChange.subscribe(myBool => {
            this.doOnAChange(myBool);
        });
    }
    ngOnDestroy() {
        this.subscription.unsubscribe();
    }
}
```
