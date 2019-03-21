# NgRX
Packages:
1. store
2. effects
3. router-store
4. store-devtools: Chrome plugin: 'Redux DevTools'
5. entity
6. schematics: angular-cli extension
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
    partialData : Observable<Data[]>;
    constructor(private store:Store<AppState>, private dataService:DataService) {

    }
    ngOnInit()
    {
        this.store
            .pipe(map(state => state.auth.loggedIn))    //extect the flag fro mthe complete state
            .subscribe(loggedIn:boolean => {console.log(loggedIn);});
        //this not yet memoized -> use better selectors(using createSelector)
        this.isLoggedIn$ = this.store.pipe(map(state => state.auth.loggedIn));
        //this memoizes
        this.isLoggedIn$ = this.store.pipe(select(isLoggedInSelector));

        const data$ = this.dataService.findAllData();
        this.partialData$ = data$.pipe(map(datas => datas.filter(data => data.category === '3')));
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
Example side effect: store credentials after login into cookies/localStorage, ...<br>
Registration in NgModule: EffectsModule.forFeature([AuthEffects]),
```ts
@Injectable()
export class AuthEffects {
    //@Effect({dispatch:true})  = use it if your effect produces another action!
    @Effect({dispatch:false})
    login$ = this.actions$.pipe(ofType<Login>(AuthActionTypes.LoginAction),tap(action:LoginAction => {
        localStorage.setItem('u', JSON.stringify(action.user);
        this.router.navigateByUrl("/data");
    })));

    //actions$ fired after a store.dispatch(...)
    constructor(private actions$: Actions, private router:Router) {}   
}
```
