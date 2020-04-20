<link rel="stylesheet" href="../../_github-markdown.css">

# NgXs

An implementiation of the Redux/Flux state management pattern for angular, incl. immutable data store (NgRx is more heavy weight, too much boilerplate).

1. docu: https://www.ngxs.io/
2. Example: https://github.com/codediodeio/ngrx-vs-ngxs/tree/master/ngxs/src/app & https://fireship.io/lessons/ngxs-quick-start-angular-state-management/

⚡️ **Install**:

$ npm -i @ngxs/{store,logger-plugin,devtools-plugin} -s

# 📖 app.module.ts
```ts
import { AppState } from './shared/app.state';
import { RouterState } from './shared/router.state';
import { NgxsModule } from '@ngxs/store';
import { NgxsReduxDevtoolsPluginModule } from '@ngxs/devtools-plugin';
import { NgxsLoggerPluginModule } from '@ngxs/logger-plugin';

@NgModule({
    /*...*/
    imports: [
        MyModule,
        NgxsModule.forRoot([                        //🚀
            RouterState,
            AppState,
        ]),
        NgxsReduxDevtoolsPluginModule.forRoot(),    //🚀
        NgxsLoggerPluginModule.forRoot()            //🚀
    ],
})
```
# 📖 shared folder
contains:
1. app.actions.ts
2. app.state.ts
3. router.state.ts

## shared/app.actions.ts
```ts
export class SetUsername {
    static readonly type = '[app set username]';
    constructor(public payload: string) { }
}
```
## shared/app.state.ts
```ts
export interface AppStateModel {
    username: string;
    status?: 'pending' | 'done' | 'rejected';
}

@State<AppStateModel>({
    name: 'app',
    defaults: {
        username: '',
    }
})
export class AppState {

    @Action(SetUsername)
    setUsername({pathState, setState, dispatch, getState }: StateContext<AppStateModel>,
                {payload}: SetUsername) {
        
        //with patchState you set some state vars, it creates a new object under the hood!
        //with setState you can replace the whole state object
        //with dispatch(SomeAction) you can call other actions (eg after async calls)
        //with getState you can get the current state

        const currentUN = getState().username;
        patchState({ username: payload });
    }

    @Action(SetUsernameAsync, {cancelUncompleted: true})
    setUsernameAsync({pathState, setState, dispatch, getState }: StateContext<AppStateModel>,
                {payload}: SetUsername) {
        patchState({ status: 'pending' });
        return this.backendService.post().pipe(
            tap(success => (success ?
                dispatch(UserNameIsSet) :
                dispatch(UserNameSetFailed)))
        );
    }
}
```
## sthared/router.state.ts
```ts
export class Navigate {
    static readonly type = '[router] navigate';
    constructor(public payload: string) { } //the payload is the path we want to navigate to
}
@State<RouterStateModel>({
    name: 'router',
    defaults: '',
})
export class RouterState {
    constructor(private router: Router) { }

    @Action(Navigate)
    async changeRoute(context: StateContext<string>, action: Navigate) {
        const path = action.payload;
        await this.router.navigate([path]);
        constext.setState(path):
    }
}
```
## A service, using RouterState
```ts
@Injectable
export class RouteHandler {
    constructor(private router: Router, private actions$: Actions) {
        this.actions$
            .pipe(ofAction(Navigate))
            .subscribe(( {payload} ) => {
                //handle the Navigate event
                //this.router.navigate([payload]);
            });
    }
}
```
## ❤️ A component, using/selecting state
```ts
@Component ({...})
export class AppComponent {

    //🚀version 1:
    state$: Observable<AppState>;
    //🚀or, version 2:    //ngxs will look for the variable called 'app'
    @Select() app$;
    //🚀or, version 3:    //specify explicitly for you select from the store
    @Select(state => state.app) app$;

    constructor(private store: Store) {
        this.state$ = this.store.select(state => state.app);

    }

    clickHandler(username) {
        this.store.dispatch([
            new SetUsername(username),
            new Navigate('/showuserdetails')
        ]);
    }
}
```
# 📖 usage in lazy loaded Feature Modules
## 🚀 lazyloaded.module.ts
```ts
@NgModule({
    /*...*/
    imports: [
        CommonModule,
        RouterModule.forChild(routes),
        NgxsModule.forFeature([SubState])
    ],
})
export class LazyLoadedFeatureModule { }
```
## sub.state.ts
```ts
export interface SubStateModel {
    substatevar: string;
}
const defaults: SubStateModel = {
    substatevar: '',
};
@State<SubStateModel>({
    substatevar: 'myvalue'
})
export class SubState {

    @Selector()
    static getSubVar(state: SubStateModel) {
        return state.substatevar.toLocaleUpperCase();
    }
}
```
## ❤️ sub.component.ts
```ts
export class MyComponent {
    //🚀 the selection API:
    @Select() substate$: Observable<any>;
    @Select(SubState.getSubVar) subvar_version1$: Observable<string>;
    @Select(state => state.substatevar) subvar_version2$: Observable<string>;
}
```
