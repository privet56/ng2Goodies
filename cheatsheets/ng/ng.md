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
    /*flex: 1; flex-ratio */
}
```
#### @angular/flex-layout
```ts
import { FlexLayoutModule } from '@angular/flex-layout';
```
```html
<forn fxLayout="column" fxLayoutAlign="center center">
    <mat-form-field style='width:300px;'><input matInput> ...
```


## Angular Material
### Setup
1. https://material.angular.io/ - with Components & CDK, eg. MatButtonModule, MatCheckboxModule from @angular/material
2. npm install --save @angular/material @angular/cdk [ for older ng-version: + @angular/animations ]
3. *BrowserAnimationsModule*, has to be added in app.module.ts
4. *styles.css*: @import "@angular/material/prebuilt-themes/indigo-pink.ss";
5. Gesture Support: npm install --save hammerjs & import 'hammerjs' in main.js;
6. &lt;link href=https://fonts.googleapis.com/icon?family=Material+Icons rel=stylesheet>
### Usage
1. html components, like
    1. &lt;button mat-icon-button color="accent">&lt;mat-icon>icon&lt;/mat-icon>&lt;/button>
    2. &lt;mat-form-field>
    3. &lt;input matInput>
1. import { MatButtonModule, MatIconMOdule } from '@angular/material';
2. import in your NgModule
