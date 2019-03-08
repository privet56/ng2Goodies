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
