# NgRx
Packages:
1. store
2. effects
3. router-store
4. store-devtools: Chrome plugin: 'Redux DevTools'
5. entity
6. schematics: angular-cli extension

Example : https://github.com/angular-university/angular-ngrx-course

## CLI
```sh
$ ng set default.schematics.collection=@ngrx/schematics   # or if newer: ng config...
$ ng generate store AppState --root --module app.module.ts
    #--> StoreModule.forRoot(reducers, {metaReducers}),
    #--> !environment.production ? StoreDevtoolsModule.instrument() : [],
    #--> reducers/index.ts is created too, defining the State & list of reducers
$ ng generate action auth/Auth
    #--> output: src/app/auth/auth.actions.ts
$ ng generate reducer Auth --flat=false --module auth/auth.module.ts
    #--> auth.reducer.ts # with AuthState, initialAuthState, ...
    #--> in auth.module.ts: StoreModule.forFeature('auth', fromAuth.reducer)
$ ng generate effect auth/Auth --module auth/auth.module.ts
    #--> new: app/auth/auth.effects.ts
    #--> modified: auth.module.ts -> EffectsModule.forFeature([AuthEffects]),
```        
## Actions
#### Example 1: Auth Actions
```ts
export enum AuthActionTypes {
    LoginActin = '[Login] Action',
    LogoutActin = '[Login] Action'
}
export class Login implements Action {
    readonly type = AuthActionTypes.LoginAction;
    constructor(public payload: {user:User}) { }    //User from app/model/user.model.ts
}
export class Logout implements Action {
    readonly type = AuthActionTypes.LogoutAction;
}
export type AuthActions = Login | Logout;
```
#### Example 1: Data Actions
```ts
export enum DataActionTypes {
    DataRequested = "[View Data Page] Data Requested",
    DataLoaded = "[Data API] Data Loaded",
    AllDatasRequested = "[Data Home Page] All Datas Requested",
    AllDatasLoaded = "[Data API] All Datas Loaded",
    DataPageRequested = "[Data Landing Page] Data Page Requested",
    DataPageLoaded = "[Data API] Data Page Loaded",
    DataPageCancelled = "[Data API] Data Page Cancelled",
}
export class DataRequested implements Action {
    readonly type = DataActionTypes.DataRequested;
    constructor(public payload:{id:number}) {}
}
export class DataLoaded implements Action {
    readonly type = DataActionTypes.DataLoaded;
    constructor(public payload:{data:Data}) {}
}
export class AllDatasRequested implements Action {
    readonly type = DataActionTypes.AllDatasRequested;
}
export class AllDatasLoaded implements Action {
    readonly type = DataActionTypes.AllDatasLoaded;
    constructor(public payload:{datas:Data[]}) {}
}
export class AllDatasCancelled implements Action {  //error case!
    readonly type = DataActionTypes.AllDatasCancelled;
}

export interface PageQuery {
    pageIndex: number;
    pageSize: number;
}
export class DataPageRequested implements Action {
    readonly type = DataActionTypes.DataPageRequested;
    constructor(public payload:{id:number, page:PageQuery}) {}
}
export class DataPageLoaded implements Action {
    readonly type = DataActionTypes.DataPageLoaded;
    constructor(public payload:{datas:Data[]}) {}
}
export class DataPageCancelled implements Action {  //error case!
    readonly type = DataActionTypes.DataPageCancelled;
}

export type DataActions = DataRequested | DataLoaded | AllDatasRequested | AllDatasLoaded;
```
## Reducers
### Reducer (app/reducers/index.ts)
```ts
export interface AppState {
    auth: AuthState,
    data: DataState
}
export const reducers: ActionReducerMap<AppState> = {
    auth: authReducer
}
//metareducer run after(before?) 'normal' reducer (eg. storeFreeze)
export conts metaReduers: MetaReducers: MetaReducer<AppState>[] = !environment.production ? [] : [];
```
### Reducer (app/reducers/reducer.auth.ts)
```ts
type AuthState = {
    loggedIn: boolean
    user: User
}
initialAuthState : AuthState = {
    loggedIn: false,
    user: undefined
}
function authReducer(state:AuthState = initialAuthState, action) : AuthState {
    switch(action.type) {
        case AuthActionTypes.LoginAction:
            return {
                ...state,
                loggedIn: true,
                user: action.payload.user
            }
        default:
            return state;
    }
}
```
### Reducer: Data Reducer
> $ ng generate entity --nam Data --module data/data.module.ts  # generates a **lot**! -> maybe better to do it manually!
```ts
import { Data } from './model/data';
export interface DataState {
    //not so efficient
        //datas: Data[];
    //Map allows access by key! -> better see below: use Map *and* Order!
        //datas: {[key:number]: Data};
    //Map & Order by do-it-yourself: (better: extends EntityState<Data>, see below)
    datasEntites: {[key:number]: Data};    //Map allows access by key!
    datasOrder: number[];
}
export interface DataState extends EntityState<Data> {
    //Nothing to do here, Map & Order is done by EntityState!
    //datasEntites: {[key:number]: Data};
    //datasOrder: number[];
    loading: boolean;
}

//use NgRx Entity:
export const adapter: EntityAdatapter<Data> = createEntityAdapter<Data>();
export const initialDataState: DataState = adapter.getInitialState({loading:false});
export function dataReducer(state = initialDataState, action: DataActions) : DataState {
    switch(action.type) {
        case DataActionTypes.AllDataRequested:
            return {
                ...state,
                loading:true
            };
        case DataActionTypes.AllDataCancelled:  //error case! 
            return {
                ...state,
                loading:false
            };
        case DataActionTypes.DataLoaded:
            return adapter.addOne(action.payload.data, state);
        case DataActionTypes.AllDataLoaded:
            return adapter.addMany(action.payload.datas, {...state, loading: false});
        default: {
            return state;
        }
    }
}

export const {
    selectAll, 
    selectIds, selectTotal, selectEntities
} = apdapter.getSelectors();
```
## Selectors
```ts
//selectors.auth.ts
import {createSelector} from '@ngrx/store';
export const selectAuthState = state => state.auth;
//it momoizes!
export const isLoggedInSelector = createSelector(selectAuthState, /*otherSelector,*/ (auth) => auth.loggedIn);

export const selectDataState = createFeatureSelector<DataState>('datas');
export const selectDataById = (id:number) => createSelector(selectDataState, dataState => dataState.entities[id]);
export const selectAllData = createSelector(selectDataState, fromData.selectAll);
export const selectPartialData = createSelector(selectAllData, datas => datas.filter(data => data.category === 'p'));

//calculate total/length/size
export const selectPTotal = createSElector(selectAllData, datas => datas.filter(data => data.category === 'p').length);
```
### Selector for **Data**
```ts
export const selectDataState = createFeatureSelector<DataState>("datas");
export const selectDataById = (id:number) => createSelector(selectDataState, dataState => dataState.entities[id]);
import * as fromCourse from '/data.reducers';
export const selectAllData = createSelector(selectDataState, fromCourse.selectAll);
export const selectDataLoading = createSelector(selectDataState, dataState => dataState.loading);

export const selectDataPage = (parentId:number, page:PageQuery) => createSelector(selectAllData,
    allDatas => {
        const start = page.pageIndex * page.pageSize,
        const end = start + page.pageSize;
        return allDatas.filter(data => data.parentId == parentId).slice(start, end);
    })
```
### Service (not NgRX-specific)
```ts
@Injectable()
export class AuthService {
    constructor(private http:HttpClient) {}
    login(mail:string, pwd:string) : Observable<User> {
        return this.http.post<user>('/api/login', {mail,pwd});
    }
}
```

## Use in Component
```ts
@Component({
    /*... template, style, selector...*/
    changeDetection: ChangeDectionStrategy.OnPush   //changes default-children-changeDetection too
})
export class MyComp  implements OnInit {

    //all the members are Observable & immutable(->storeStat)? -> you can use OnPush -> speedup boost!
    isLoggedIn$ : Observable:<boolean>;
    partialData$ : Observable<Data[]>;
    pTotal$ : Observable<number>;
    loading$ : Observable<boolean>;

    constructor(private store:Store<AppState>, private dataService:DataService) {  }

    ngOnInit()
    {
        this.store
            .pipe(map(state => state.auth.loggedIn))    //extect the flag fro mthe complete state
            .subscribe(loggedIn:boolean => {console.log(loggedIn);});

        //request to fetch data from server via @Effect!
        this.store.dispatch(new AllDataRequested());

        //this not yet memoized -> use better selectors(using createSelector)
        this.isLoggedIn$ = this.store.pipe(map(state => state.auth.loggedIn));
        //this memoizes
        this.isLoggedIn$ = this.store.pipe(select(isLoggedInSelector));

        const data$ = this.dataService.findAllData();
        this.partialData$ = data$.pipe(map(datas => datas.filter(data => data.category === 'p')));

        //with selectors, it will be memoized
        this.partialData$ = this.store.pipe(select(selectPartialData));

        //calculate total/length/size
        this.pTotal$ = this.store.pipe(select(selectPTotal));

    	this.store.dispatch(new AllDataRequested());
        this.datas$ = this.store.pipe(select(selectAllData));

        this.loading$ = this.store.pipe(select(selectDataLoading));

        {
            const initialPage: PageQuery { pageIndex: 0, pageSize: 3};
            this.store
        }
    }
    login() {
        this.authService.login(mail,pwd)
            pipe(tap(user => {
                this.store.dispatch(new Login({user}));
                this.router.navigateByUrl('/data');
            }))
            .subscribe(
                noop/*from RxJS*/,
                () => {alert('failure');}
            );
    }
    logout() {
        this.store.dispatch(new Logout());
    }
}
```
```html
<a mat-list-item routerLink="/logout" *ngIf="isLoggedIn$ | async"> ... </a>
<data-card-list [data]="partialData$ | async" />
<p> Number of P: {{pTotal$ | async }} </p>
<div class="spinner-container" *ngIf="loading$ | async"><mat-spinner></mat-spinner></div>

```
## NgModule to be extended:
```ts
    StoreModule.forFeature('auth', fromAuth.reducer),
    StoreModule.forFeature('datas', dataReducer)
```

## Use in Router Guard
const routes: Routes = [ /*...*/ path:'/data', canActivate: [AuthGuard], 
```ts
@Injectable()
export class AuthGuard implements CanActivate {
    constructor(private store:Store<AppState>, private router:Router) { }
    canActivate(route: ActivatedRouteSnapshot, state:RouterStateSnaphot) : Observable<boolean> {
        //return this.store.pipe(select(isLoggedInSelector));
        return this.store.pipe(select(isLoggedInSelector), tap(loggedIn => {
            if(!loggedIn) 
                this.router.navigateByUrl('/login');
        }));
    }
}
```
## Effects
Side effects listen to store changes and do side effects.<br>
Example side effect: store credentials after login into cookies/localStorage, ...<br>
Registration in an NgModule: EffectsModule.forFeature([AuthEffects, DataEffects]),<br>
Registration in the main NgModule, addionally: EffectsModule.forRoot([])
```ts
@Injectable()
export class AuthEffects
{
    //@Effect({dispatch:true})  = use it if your effect produces another action!
    @Effect({dispatch:false})
    login$ = this.actions$.pipe(ofType<Login>(AuthActionTypes.LoginAction),tap(action:LoginAction => {
        localStorage.setItem('u', JSON.stringify(action.user);
        this.router.navigateByUrl("/data");
    })));

//defer() + of(...) are from RxJS
//defer() = will be executed on startup, after the app is initialized!
    @Effect({dispatch:true})
    init$ = defer(() => {
        const userData = localStorage.getItem('u');
        if(userData) {
            return of(new Login(JSON.parse(userData)));
        }
        else {
            return of(new Logout());//dispatch:true -> you need to return an Observable in any case!
        }
    });
}
@Injectable()
export class DataEffects
{
//loads data when requested by dispatching an action    //see also below extension with Entity/cache/withLatestFrom...
    @Effect()
    loadAllData$ = this.actions$.pipe(
        ofType<AllDataRequested>(DataActionTypes.AllDataRequested),
        //switchMap would cancel the original request
        //mergeMap allows multiple parallel requests
        mergeMap(action => this.dataService.findAllData().pipe(
            catchError(err => {
                console.log(err);
                this.store.dispatch(new AllDataCancelled());
                return of([]);
            }),
        )),
        map(datas => new AllDataLoaded({datas}))
    );

    @Effect()
    loadData$ = this.actions$.pipe(
        ofType<DataRequested>(DataActionTypes.DataRequested),
        //mergeMap allows multiple parallel requests
        //emits a Data object
        mergeMap(action => this.dataService.findDataById(action.payload.id)),
        map(data => new DataLoaded({data}))
    );

    //actions$ fired after a store.dispatch(...)
    constructor(private actions$: Actions, private router:Router) {}   
}
```
### Store Freeze
NgRx addon making sure that reducer doesn't change input data but creates new object!
https://github.com/brandonroberts/ngrx-store-freeze<br>
npm i --save-dev ngrx-store-freeze<br>

```ts
export const metaReducers: MetaReducer<AppState>[] = !environment.production ? [storeFreeze] : [];
```
### @ngrx/router-store
NgRx addon for the store-devtools Chrome plugin<br>
npm install @ngrx/route-store --save<br>
Serializes the router state to the store (best to take also the custom serializer from the docu)<br>
With this, the **time travel debugger** function works fine!
```ts
@NgModule({ import[ ...
StoreRouterConnectingModule.forRoot({stateKey:'router'})
//and:
export const reducers: ActionReducerMap<AppState> = {
    router: routerReducer
}
```
## NgRx Entity
Serves as a ~cache (complicated as hell, because implementation spread over different parts)
```ts
//data.effects.ts
    @Effect()
    loadAllData$ = this.actions$.pipe(
        ofType<DataRequested>(DataActionTypes.DataRequested),
        withLatestFrom(this.store.pipe(select(allDataLoaded))),
        filter(([action, allDataLoaded]) => !allDataLoaded),
        mergeMap(action => this.dataService.findAllData()),
        map(datas => new AllDataLoaded({datas}))
    );
// data.actions.ts
// the >>Update<< ~flags the Data Entity to have been changed! --> update cache!
export class DataSaved implements Action {
    readonly type = DataActionTypes.DataSaved;
    constructor(public payload: {data:Update<Data>}) { }
}
// data.reducers.ts
export interface DataState extends EntityState<Data> {
    allDataLoaded:boolean;
}
export const adapter : EntityAdapter<Data> = createEntityAdapter<Data>();
export const initialDataState : DataState = adapter.getInitialState({allDataLoaded:false});
export function dataReducer(state = iniitalDataState, action: DataAction) : DataState {
    switch(action.type) {
        case DataActionTypes.Dataloaded:
            return adapter.addOne(action.payload.data, state);
        case DataActionTypes.AllDataLoaded:
            return adapter.addAll(action.payload.datas, {...state, allDataLoaded:true});
        case DataActionTypes.DataSaved:
            //adapter can updatMany, updateOne, upsertMany, upsertOne
            return adapter.updateOne(action.payload.data, state);
        default:
            return state;
    }
}
//component
    save() {
        this.dataService.saveData(id, data)
            .subscribe(() => {
                const updateData: Update<Data> = {
                    id: id,
                    changes: data   //changes:Partial<Data> , allows listing only the changed values!
                };
                this.store.dispatch(new DataSaved({updateData}));
                this.dialogRef.close();
            });
    }
```
# Resolver
```ts
@Injectable()
export class DataResolver implements Resolve<Data> {
    constructor(private dataService:DataService, private store:Store<AppState>)     {}
    resolve(route:ActivatedRouteSnapshot, state: RouterStateSnapshot) : Observable<Data> {
        const id = route.params["id"];
        //naive implementation rereading, because no cache
        return this.dataService.findDataById(id);
        //better: use EntityAdapter:
        return this.store.pipe(
            select(selectDataById(id)),
            tap(data => {
                if(!data)//not yet in store(~cache) of EntityAdapter
                    this.store.dispatch(new DataRequested({id}));
            }),
            //if(no data yet) -> do not continue the router transition!
            filter(data => !!data), 
            // make sure that the Observable completes/terminates, so the router transition completes!
            //otherwie the target route is never reached
            first()
        );
    }
}
```
## Advanced Stuff
#### Set up Entity Default Sort Order
```ts
function sortByDataAndSeqNo(d1:Data, d2:Data) {
    const compare = d1.id - d2.id;
    if(compare != 0) return compare;
    return d1.seqNo - d2.seqNo;

}
export const adapter: EntityAdatapter<Data> = createEntityAdapter<Data>({
    sortComparer: sortByDataAndSeqNo
});
```
#### Paginagor in Data Source
```ts
export class DataDataSource implements DataSource<Data> {
    private datasSubject = new BehaviorSubject<Data[]>([]);
    constructor(private store:Store<AppState>) { }
    loadDatas(id:number, page: PageQuery) {
        this.store.pipe(
            select(selectDataPage(id, page)),
            tap(datas => {
                if(datas.length > 0) { //=is already in store
                    this.datasSubject.next(datas);
                }
                else
                {
                    this.store.dispatch(new DataPageRequested({id, page}));
                }
            }),
            catchErro(err => of([]))
        )
        .subscribe();
    }
    //these functions are helpers for angular-material datatable
    connect(collectionViewer:CollectionViewer) : Observable<Data[]> {
        return this.datasSubject.asObservable();
    }
    disconnect(collectionViewer:CollectionViewer) : void {
        this.datasSubject.complete();
    }
}

//Use in Component:
@Component({
    template: `<mat-table [dataSource]="dataSource"> ... <mat-header...>+<mat-row...>... </mat-table>
                <mat paginator [length]="data?.dataCount" [pageSize]="3"></mat paginator>`,
    ...
})
export class MyComponent implements OnInit, AfterViewInit {
    data:Data;
    dataSource:DataDataSource;
    displayedColumns=["seqNo", "title"];
    @ViewChild(MatPaginator) paginator: MatPaginator;
    constructor(private route:ActivatedRoute, private store: Store<AppState>) { }
    ngOnInit() {
        this.data = this.route.snapshot.data["data"];
        this.dataSource = new DataDataSource(this.store);
        const initialPage: PageQuery = {
            pageIndex: 0,
            pageSize: 3
        };
        this.dataSource.loadDatas(this.data.id, initialPage);
    }
    ngAfterViewInit() {                         //=here, @ViewChild is available
        this.paginator.page.pipe(               //subscribe to the paginator.page event
            tap(() => this.loadDataPage())
        ).subscribe();
    }
    loadDataPage() {
        const newPage: PageQuery = {
            pageIndex: this.paginator.pageIndex,
            pageSize: this.paginator.pageSize
        };
        this.dataSource.loadData(this.data.id, newPage);
    }
}

// The Effect for Loading the Data Page (data.effects.ts)
...
    @Effect()
    loadDataPage$ = this.actions.pipe(
        ofType<DataPageRequested>(DataActionTypes.DataPageRequested),
        mergeMap(({payload}) =>
            this.dataService.findData(payload.id, payload.pageIndex, payload.pageSize)),
            map(datas => new DataPageLoaded({datas}));
    );

// Reducer(data.reducers.ts)
...
export functin dataReducer(state = initialDataState, action: DataActions) : DataState {
    switch(action.type) {
        case DataActionTypes.DataPageLoaded:
            return adapter.addMany(action.payload.datas, state);
        default:
            return state;
    }
}

//Service: http call in data.service.ts
...
    findData(id: number, pageNumber= 0, pageSize: 3): Observable<Data[]> {
        return this.http.get("/api/data", {
            params: new HttpParams()
                .set('id', id)
                .set('page', pageNumber)
                .set('pageSize', pageSize)
        }).pipe(map(res => res["payload"]));
    }
```
