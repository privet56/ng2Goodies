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
import {Action,StoreModule,ActionReducerMap, createFeatureSelector, createSelector} from '@ngrx/store';
//ACTIONS: ui.actions.ts
export const START_LOADING '[UI] Start Loading';
export const STOP_LOADING '[UI] Stop Loading';
export class StartLoading implements Action {
    readonly type = START_LOADING;
    constructor(public payload: data[]) { }
}
export class StopLoading implements Action {
    readonly type = STOP_LOADING;
    constructor(public payload: data[]) { }
}
export type UIActions = StartLoading | StopLoading;

//REDUCER: ui.reducer.ts
import {UIActions, START_LOADING, STOP_LOADING} from './ui.actions';
interface State {
    isLoading: boolean;
    data: string[];
}
const initialState:State = {
    isLoading = false;
    data = [];
};
export function uiReducer(state = initialState, action:UIActions) {
    switch(action.type)
    {
        case START_LOADING:
            return { ...state, isLoading: true, data: action.payload};
        case STOP_LOADING:
            return { ...state, isLoading: false, data: action.payload};
        default:
            return state;
    }
}
export const getIsLoading = (state:State) => state.isLoading;

//REDUCER: data.reducer.ts
import * as fromRoot from 'app.reducer';
export interface DataState {
    data1: string[],
    data2: string[]
}
//this way, you dont need to import data.reducer inside of app.reducer! -> you can lazy load!
export interface State extends fromRoot.State {
    data: DataState;
}
const initialState:DataState = {
    data1: [],
    data2: []
};
export function dataReducer(state = initialState, action:DataActions) {
    switch(action.type)
    {
        case START_DATA:
            return { ...state, data1: action.payload};
        default:
            return state;
    }
}
export const getDataState = createFeatureSelector<DataState>('data'/*=as in  StoreModule.forFeature('data' */);
export const getData1 = createSelector(getDataState, (state:DataState) => state.data1);
export const hasData1 = createSelector(getDataState, (state:DataState) => state.data1 != null);

//ALL-REDUCER: app.reducer.ts
import * as fromUi from 'ui.reducer';
export interface State {
    ui: fromUi.State;
    auth: fromAuth.State;
}
export const reducers:ActionReducerMap<State> = {
    ui:fromUi.uiReducer,
    auth:fromAuth.authReducer
    //data:fromData.dataReducer //no! you will lazy-load!
};
export const getUiState = createFeatureSelector<fromUi.State>('ui');
export const getIsLoading = createSelector(getUiState, fromUi.getIsLoading);

//STORE: app.module.ts
    imports: [
        ,
        StoreModule.forRoot(reducers)
        //alternative, if you only need some of the reducers, lazy-loaded!
        StoreModule.forFeature('data'/*as in getDataState */ ,dataReducer)
    ],

//CMPONENT or SERVICE: my.comp.ts
import * as fromRoot from 'app.reducer';
import * as UI from 'ui.actions';
export My {
    isLoading$: Obervable<boolean>;
    constructor(private store:Store<fromRoot.State>) { }
    //constructor(private store:Store<fromData.State>) { }//in a lazy-loaded module!
    ngOnInit() {
        //no unsubscribe necessary ... :-)
        this.isLoading$ = this.store.select(fromRoot.getIsLoading);
        this.hasData$ = this.store.select(fromData.hasData1);

        //get data1 only now & once!
        this.store.select(fromData.getData1).pipe(take(1)).subscribe(data1 => {
            //save data1 to database...
        });
    }
    doLoadStart() {
        this.store.dispatch(new UI.StartLoading(myPayload));
    }
    //in a Guard:
    canActivate(route:ActivatedRouteSnapshot, state:RouterStateSnapshot) {
        return this.canLoad(null);
    }
    canLoad(route:Route) {
        return this.store.select(fromRoot.getIsAuth).pipe(take(1)); 
    }
}

//html: *ngIf="!(isAuth$ | async)"
```
