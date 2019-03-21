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
```ts
export enum AuthActionTypes {
    LoginActin = '[Login] Action';
    LogoutActin = '[Login] Action';
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
## Reducers (app/reducers/index.ts)
```ts
export interface AppState {
    auth: AuthState,
    //data: DataState
}
export const reducers: ActionReducerMap<AppState> = {
    auth: authReducer
}
//metareducer run after(before?) 'normal' reducer (eg. storeFreeze)
export conts metaReduers: MetaReducers: MetaReducer<AppState>[] = !environment.production ? [] : [];
```
## Reducer (app/reducers/reducer.auth.ts)
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
## Selectors
```ts
//selectors.auth.ts
import {createSelector} from '@ngrx/store';
export const selectAuthState = state => state.auth;
//it momoizes!
export const isLoggedInSelector = createSelector(selectAuthState, /*otherSelector,*/ (auth) => auth.loggedIn);

export const selectDataState = createFeatureSelector<DataState>('data');
export const selectDataById = (id:number) => createSelector(selectDataState, dataState => dataState.entities[id]);
export const selectAllData = createSelector(selectDataState, fromData.selectAll);
export const selectPartialData = createSelector(selectAllData, datas => datas.filter(data => data.category === 'p'));

//calculate total/length/size
export const selectPTotal = createSElector(selectAllData, datas => datas.filter(data => data.category === 'p').length);
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
@Component({/*...*/})
export class MyComp  implements OnInit{
    isLoggedIn$ : Observable:<boolean>;
    partialData$ : Observable<Data[]>;
    pTotal$ : Observable<number>;
    constructor(private store:Store<AppState>, private dataService:DataService) {

    }
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

```
## NgModule to be extended:
```ts
    StoreModule.forFeature('auth', fromAuth.reducer)
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
Registration in an NgModule: EffectsModule.forFeature([AuthEffects]),<br>
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

//loads data when requested by dispatching an action    //see also below extension with Entity/cache/withLatestFrom...
    @Effect()
    loadAllData$ = this.actions$.pipe(
        ofType<DataRequested>(DataActionTypes.DataRequested),
        mergeMap(action => this.dataService.findAllData()),
        map(datas => new AllDataLoaded({datas}))
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
