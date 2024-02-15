<link rel="stylesheet" href="../_github-markdown.css">

## Reusable Angular Animation:
**BrowserAnimationsModule**, has to be added in app.module.ts
```ts
//// anim.ts
import {animation, trigger, animateChild, group, transition, animate, style, query} from '@angular/animations';
export const transAnimation = animation([
    style({
        height:'{{ height }}',
        opacity:'{{ opacity }}',
        backgroundColor:'{{ backgroundColor  }}'
    }),
    animate('{{ time }}')
]);
//// my-comp.ts
import { transAnimation } from 'anim.ts';
@Component({
    selector: 'my-comp',
    templateUrl: './my-comp.html',
    styleUrl: './my-comp.css',
    animations: [
        trigger('anim', [
            transition('open => closed', [
                useAnimation(transAnimation, {
                    params: {
                        height: 0,
                        opacity: 1,
                        backgroundcolor:'red',
                        time: '1s'
                    }
                })
            ])
        ])
    ]
})
class My
{
    isOpen = true;
    toggle() {
        isOpen = !isOpen;
    }
}
```
```html
<div [@anim]=isOpen ? 'open' : 'closed'" class="open-close-container"> ... </div>
```
## Flex Layout
use https://github.com/angular/flex-layout/ for flexbox : npm install @angular/flex-layout --save
#### Standard CSS flexbox (take care of older IE versions...):
```css
#container {
    display:flex;
    width:100%;
    height:777px;
    flex-direction:row;
    justify-content:flex-start;
    align-items:center;
}
.child {
    width:333px;
    height:333px;
    /*flex: 1; = flex-ratio */
}
```
#### @angular/flex-layout
```ts
import { FlexLayoutModule } from '@angular/flex-layout';

onSubmit(f:NgForm) { }
```
##### HTML with FlexBox **and** Angular Material Control
```html
<forn fxLayout="column" fxLayoutAlign="center center" #f="ngForm" (ngSubmit)="onSubmit(f)">
    <mat-form-field style='width:300px;'>
     <!-- standard validations: email, required,minlen -->
     <input matInput ngModel name="mail" email required minlength="6" hintLabel="sure?" #myinp="ngModel">
        <!-- Angular Material component: mat-hint, mat-error (hintLabel too) -->
        <mat-hint align="end"> value length: {{myinp.value?.length}} </mat-hint>
        <mat-error *ngIf="myinp.hasError('required')">that is empty</mat-error>
        <mat-error>that is invalid</mat-error>

 <div fxFlex fxLayout fxLayoutAlign="flex-end" fxHide.xs>   <!-- hide if screen <= xs -->
 <div fxFlex fxLayout fxLayoutAlign="flex-end" fxHide.gt-xs><!-- hide if screen gt xs -->
 <div fxFlex.xs="100%" fxFlex="400px">                      <!-- different values, based on device -->
```
## Angular Material
### Setup
1. https://material.angular.io/ - with Components & CDK, eg. MatButtonModule, MatCheckboxModule from @angular/material
2. npm install --save @angular/material @angular/cdk [ for older ng-version: + @angular/animations ]
3. *BrowserAnimationsModule*, has to be added in app.module.ts
4. *styles.css*: @import "@angular/material/prebuilt-themes/indigo-pink.css";
5. Gesture Support: npm install --save hammerjs & import 'hammerjs' in main.js;
6. &lt;link href=https://fonts.googleapis.com/icon?family=Material+Icons rel=stylesheet>
### Usage
1. html components, like
    1. &lt;button mat-icon-button color="accent|primary">&lt;mat-icon>icon&lt;/mat-icon>&lt;/button>
    2. &lt;mat-form-field>
    3. &lt;input matInput>
    4. &lt;mat-drawer-container>    &lt;mat-drawer mode="side" opened="true">&lt;mat-drawer-content>
    5. &lt;mat-sidenav-container>   &lt;mat-sidenav #sn>&lt;mat-sidenav-content>&lt;router-outlet>  //sn.toggle();
    6. &lt;mat-card> //with mat-card-content ...
    7. &lt;mat-select placeholder="..."> &lt;mat-option value="...">
    8. MatSnackBar (like Android Toast)
1. import { MatButtonModule, MatIconMOdule } from '@angular/material';
2. import in your NgModule
#### Date Picker
1. use with MatMomentDateModule (dependency: moment.js) (import: @angular/material-moment-datapter)
    (MatDatePickerModule & MatNativeDateModule is the basic version without moment.js)
2. ts/html code is complicated...
    1. &lt;input matInput [matDatepicker]="p">&lt;mat-datepicker-toggle matSuffix [for]="p">&lt;mat-datepicker #p>...
#### MatDialog
```ts
@Component({
    selector: 'my-dlg-content',
    template: `<h1 mat-dialog-title></h1>
                <mat-dialog-content>{{data.mydata}}</mat-dialog-content>
                <mat-dialog-actions><button mat-button [mat-dialog-close]="false">
                ...`
})
export class MyDlgContent {
    constructor(@Inject(MAT_DIALOG_DATA) public data:any)  { console.log(data.mydata); }
}
//app.module.ts: entryComponents: [MyDlgContent]
//later: open dialog
const dlgRef = matDialog.open(MyDlgContent, {data:{mydata:1}});
dlgRef.afterClosed().subscribe(result => { console.log(result/* value of mat-dialog-close */); })
```
## Angular Material Theming
create my-theme.scss (in dir of styles.css). Use the syle & color guide to choose colors.
```css
@import '~@angular/material/theming';
@include mat-core();
/*define your own colors! */
$candy-app-primary: mat-palette($mat-indigo/*$mat-red*/);
$candy-app-accent: mat-palette($mat-pink, A200, A100, A400);

$candy-app-theme: mat-light-theme($candy-app-primary, $candy-app-accent, $candy-app-warn);

@include angular-material-theme($candy-app-theme);
```
.angular-cli.json -> "styles": [ ..., "my-theme.scss"]

# AuthGard
```ts
import { CanActivate } from '@angular/router';
@Injectable()
export class AuthGuard implements CanActivate {
    constructor(private authServ:AuthService, private router:Router) {}
    canActivate(route:ActivatedRouteSnapshot, state:RouterStateSnapshot) {
        if(this.authServ.isAuth())return true;
        this.router.navigate(['/login']);
    }
}
//usage: app.routing.module.ts
const routes:Routes = [
    {path:'data', component:DataComp, canActivate:[AuthGuard]}
    ...
];
//...
@NgModule({
    ...
    providers: [AuthGuard]
})
```
### Material - DataTable
```html
<mat-table #tbl [dataSource]="dSource" matSort>
    <ng-container matColumnDef="name"><-- = a column -->
        <mat-header-cell *matHeaderCellDef mat-sort-header>Name</mat-header-cell>
        <mat-cell *matCellDef="let ele">{{ele.name}}</mat-cell>
     </ng-container>
    <!-- ...other columns ... -->
    <mat-header-rows *matHeaderRowDef="diplayedColumns"></mat-header-rows>
    <mat-row *matRowDef="let row;columns:displayedColumns;"></mat-row>
</mat-table>
<!-- paginator -->
<mat-paginator #pagi [pageSize]="10" [pageSizeOptions]="[5,10,20]"><mat-paginator>
<!-- filter -->
<div fxLayoutAlign="center center">
<mat-form-field fxFlex="50%"><!-- center horizontally & make 50% width -->
    <input matInput type="text" (keyup)="doFilter($event.target.value)" 
placeholder="Filter" />
</mat-form-field>
<div>
```
```ts
//@NgModule: import MatTableModule, MatSortModule, MatPaginatorModule
//component
export class TblComp implements OnInit, AfterViewInit {
    displayedColumns = ['name','date'];
    dataSource = new MatTableDataSource<MyModel>();
    @ViewChild(MatSort) sort:MatSort;
    @ViewChild(MatPaginator) pagi:MatPaginator;

    constructor(private myServ:MyService) {}
    ngOnInit() {
        this.dataSource.data = this.myServ.getDatas().slice(/*=copy array!*/);
    }
    ngAfterViewInit() {
        this.dataSource.sort = this.sort;
        this.dataSource.paginator = this.pagi;
    }
    doFilter(val:string) {
        this.dataSource.filter = val.trim().toLowerCase();//use 'filterPredicate' if filtering logic to be changed...
    }
}
```
## Firebase & AngularFire2 & Firestore & its Auth
* https://github.com/angular/angularfire2 -> $ npm install angularfire2 firebase --save
* @NgModule : import {AngularFireModule} from 'angularfire2'; -> import AngularFireModule.initalizeApp(environment.fb), AngularFirestoreModule;
    * AngularFireAuth
    * AngularFirestore
    * AngularFire
* angularFirestore.collection('mycol').valueChanges().subscribe(re => { });
```ts
data$: Observable<any>;
ngOnInt() {
    data$ = angularFirestore.collection('mycol').valueChanges();    //-> real time update! :-) ; without id :-(

    //snapshotChanges() = alternative to valueChanges(), but includes
    //type of change (added, changed, ...) & payload.doc:DocumentSnapshot with
    //id,metadata,ref,data
    data$ = angularFirestore.collection('mycol').snapshotChanges() //data$.payload.doc.data()
        .map(dataArray:Array<any> => {
            return dataArray.map(doc => {
                id: doc.payload.doc.id,
                ...doc.payload.doc.data()
            })
        });
}
addData(data:Data) {
    angularFirestore.collection('mycol').add(data);
}
registerUser() {
    //Auth Sign-in provider Email/pwd has to be activated on the firebase web ui
    //angularFireAuth is stateless, uses Token
    angularFireAuth.auth.createUserWithEmailAndPassword(email, pwd)
        .then(re => {

        })
        .catch(err => {
            //eg. email already taken
        });
}
loginUser() {
    angularFireAuth.auth.signInWithEmailAndPassword(email, pwd)
        .then(re => {

        })
        .catch(err => {
            //eg. invalid credentials
        });
}
//html: use: data$ | async
```
## Lazy Loaded @NgModule
1. **Child** has an own router, but
    * imports: [RouterModule.forChild(routes)], exports: [RouterModule]
2. **Root** module has route to the child(=lazy-loaded) module only as string, but no import! (=app.routing.module):
    * { path: 'child', loadChildren: './child/child.module.ts#MyChildModule' }
3. Result: Child @NgModule will only loaded when navigated to it.

## Trick: make sure that your CoreModule will not be imported multiple times
```ts
import { NgModule, Optional, SkipSelf } from '@angular/core';
import { CommonModule } from '@angular/common';
@NgModule({
    imports: [
        CommonModule,
    ],
    providers: []
})
export class CoreModule
{
    constructor(@Optional() @SkipSelf() parentModule: CoreModule)
    {
        if (parentModule) {
            throw new Error(`CoreModule has already been loaded. Import Core modules in the AppModule only!`);
        }
    }
}
```
## Short & sweet ngIf/else & ngFor

```html
<div *ngIf="notes$ | async as notes; else notFound">
    <app-note-card *ngFor="let note of notes" [note]="note" [loading]="isLoading$ | async"
        [routerLink]="['/notes', note.id]">
    </app-note-card>
</div>
<ng-template #notFound><!-- else -->
    <mat-card>
        <mat-card-title>Either you have no notes</mat-card-title>
    </mat-card>
</ng-template>
```
## Listen to DOM style changes with MutationObserver
```ts
ngAfterViewInit(): void {

    const that = this;
    const pEle = this.el.nativeElement.parentNode;

    const observer = new MutationObserver((mutations) => {
        mutations.forEach((mutation) => {
            if( (mutation.type === "attributes") &&
                (mutation.attributeName === "ng-reflect-view"))
            {
                let computedStyle = window.getComputedStyle(pEle);

                if( (that.parentDisplayAttribute !== computedStyle.display) &&
                    (computedStyle.display === 'block'))
                {
                    console.log("ele is visible:"+that.parentDisplayAttribute+" => "+computedStyle.display);
                }
                that.parentDisplayAttribute = computedStyle.display;
            }
        });
    });

    observer.observe(pEle, {
        //attributeFilter: ['style', 'class'],
        attributeOldValue: true,
        attributes: true,
        characterData: true,
        characterDataOldValue: true,
        childList: true,
        subtree: true
    });
}
```
### SSR Support:
Use App Shell:
```sh
$ ng generate app-shell --client-project [my-app] --universal-project [server-app]
$ ng run [project-name]:app-shell:production
```

### Visualize generated Webpack Bundle contents:
```sh
$ ng build --prod --stats-json
$ webpack-bundle-analyzer dist/stats.json
```
## PWA technologies
1. **offline** support
    * for static data, with Service Workers (<span class=cmd>ng add @angular/pwa</span>).
        Events, like
        * <span class=code>self.oninstall = (event) => { };</span>
        * <span class=code>self.onactivate = (event) => { };</span>
    * for dynamic data, eg. with PouchDB(-browser) or firebase(<span class=cmd>npm install firebase @angular/fire –-save</span>)
        * <span class=cmd>npm install pouchdb-browser</span> & <span class=cmd>npm install -g pouchdb-server</span>
    * service worker generator: <span class=cmd>npm install workbox-cli --global</span>
1. **add-to-homescreen** function (incl. events like <span class=code>@HostListener('window:beforeinstallprompt', ['$event'])</span>)
1. **push notification**:
    * <span class=code>navigator.serviceWorker.ready.then(sw => sw.showNotification('title', {icon:'m.png'}));</span>
    * Ng2+ lib: SwPush
    * Server side package: <span class=code>require('web-push')</span>
1. Visualize connection speed:
    * <span class=code>const { downlink, effectiveType, type } = (&lt;any&gt;navigator).connection;</span>
        * console.log(`Effective network connection type: ${effectiveType}`);
        * if (/\slow-2g|2g|3g/.test((<any>navigator).connection.effectiveType)) { this.snackBar.open(`Your connection is slow!`); }
        * console.log(`Downlink Speed/bandwidth estimate: ${downlink}Mb/s`);
        * console.log(`${type} could be of bluetooth, cellular, ethernet, none, wifi, wimax, other, unknown`);
1. Advanced/beta browser APIs:
    * Credential management ((window.PasswordCredential || window.FederatedCredential)
    * Payment: window.PaymentRequest
    * Audio/Video Recording: window.MediaRecorder
    * Geolocation: navigator.geolocation
    * navigator.bluetooth
    * navigator.usb

## Control lazy loading:
* use **canLoad** Guard (<span class=code>canLoad: [AuthGuard]</span>)
    or
* use preload flag: <span class=code>RouterModule.forRoot(routes, { **preloadingStrategy: PreloadAllModules** })</span>

## Load PDF with Ajax
(eg. because of restrictive X-Frame-Options)

HTML:
```html
<embed #domElement width="375" height="375" type="application/pdf" class="embed">
```
TS Code:
```ts
ngAfterViewInit() { // i will access this.domElement.nativeElement, so i need DOM when beginning!
    const startTime: Date = new Date();
    this.loadingPdf = true;
    const pdfUrl: string = 'https://my.server.org/my-cors-pdf.pdf';
    fetch(pdfUrl).then((response: Response) => response.blob()).then((blob: Blob) => {
        const url: string = window.URL.createObjectURL(blob);
        this.domElement.nativeElement.src = url;
        this.loadingPdf = false;
        const loaded = 'Loaded in ' + DateUtil.getShortTimeDiffAsReadable(startTime, new Date());

        this.domElement.nativeElement.parentElement.title =
            this.domElement.nativeElement.parentElement.title = loaded;

    }).catch((error) => {
        this.loadingPdf = false;
        this.onError('Error occured:', error);
    });
}
```
