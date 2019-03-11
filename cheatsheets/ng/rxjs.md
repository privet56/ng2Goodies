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
# NgRx = RxJS|Redux for Ng2+
> $ npm install --save @ngrx/store @ngrx/effects

Example:
```ts
//REDUCER: ui.reducer.ts
//ALL-REDUCER: app.reducer.ts
interface State {
    isLoading: boolean;
}
const initialState:State = {
    isLoading: boolean = false;
};
export function uiReducer(state = initialState, action) {
    switch(action.type)
    {
        case 'START_LOADING':
            return { isLoading: true};
        case 'STOP_LOADING':
            return { isLoading: false};
        default:
            return state;
    }
    return state;
}

//STORE: app.module.ts
import {StoreModule} from '@ngrx/store';

    imports: [
        ,
        StoreModule.forRoot({ui: appReducer})
    ],

//CMPONENT or SERVICE: my.comp.ts
import * as fromApp from 'app.reducer.ts';
export My {
    isLoading$: Obervable<boolean>;
    constructor(private store:Store<{ui:fromApp.State}>) { }
    ngOnInit() {
        //this.store.subscribe(data => {});
        this.isLoading$ = this.store.map(state => state.ui.isLoading); //no unsubscribe necessary ... :-)
    }
    doLoadStart() {
        this.store.dispatch({type:'START_LOADING' });
    }
    onLoadStarting() {

    }
}
```
