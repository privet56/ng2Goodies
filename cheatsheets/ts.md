# TypeScript CheatSheet

## How to reference a class attribute **name** as string safely?

```ts
// 1. define the 'nameOfFactory' helper utility function (a generic template function):
export const nameOfFactory = <T>() => (name: keyof T) => name;

// 2. define ts class with static 'nameOf' type-specific helper
export class MyEntity {

    static readonly nameOf: (name: keyof MyEntity) => keyof MyEntity = nameOfFactory<MyEntity>();

    myAttribute: string;
}

// 3. in your component:
@Component({
    selector: 'app-my-entity-view',
    templateUrl: './my-entity-view.component.html',
})
export class MyEntityViewComponent implements AfterViewInit {

    MyEntityNameOf: (name: keyof MyEntity) => keyof MyEntity = MyEntity.nameOf;
    // ...
}
```
```html
<!-- 4. use in html template 'my-entity-view.component.html': -->
<!-- ok, a known valid attribute name, MyEntity.myAttribute: -->
<span [ngClass]="{'foo' : sort === MyEntityNameOf('myAttribute') }"></span>
<!-- your editor will show an error, as MyEntity.anUnknownAttr is invalid: -->
<span [ngClass]="{'foo' : sort === MyEntityNameOf('anUnknownAttr') }"></span>
```

## How to simplify repeated html structures in a template?
(eg. when you can't use *ngFor)

```html
<!-- 1. define template -->
<ng-template #sortHeader let-text='text' let-showFilter='showFilter'>
    {{text}}
    <div class="my-class" *ngIf="showFilter">Filter!</div>
</ng-template>

<!-- 2. use template as often as needed -->
<ng-container [ngTemplateOutlet]="sortHeader"
              [ngTemplateOutletContext]="{text: 'Mandant Name', showFilter: true}">
</ng-container>
<div> ...some other content... </div>
<ng-container [ngTemplateOutlet]="sortHeader"
              [ngTemplateOutletContext]="{text: 'Mandant Adresse', showFilter: false}">
</ng-container>
```

## ng-template type safe?
(same issue as above, but this time with type safe parameters)

```html
<!-- 1. define template, use SortCfg.as(cfg) to cast variable to the correct type -->
<ng-template #sortHeader let-cfg='cfg'>
    {{SortCfg.as(cfg).attri}}
    <div class="my-class" *ngIf="SortCfg.as(cfg).showFilter">Filter!</div>
</ng-template>

<!-- 2. use template as often as needed -->
<ng-container [ngTemplateOutlet]="sortHeader"
              [ngTemplateOutletContext]="{cfg: new SortCfg('MandantName', true)}">
</ng-container>
<div> ...some other content... </div>
<ng-container [ngTemplateOutlet]="sortHeader"
              [ngTemplateOutletContext]="{cfg: new SortCfg('MandantAddress', false}">
</ng-container>
```
```ts
// 3. define SortCfg (not needed to be exported, as used only in my template):
class SortCfg {
    constructor(public attri: keyof MyEntity, public showFilter: boolean) {
    }

    static create(attri: keyof MyEntity, showFilter: boolean): SortCfg {
        return new SortCfg(attri, showFilter);
    }

    static as(sortHeaderCfg: any): SortHeaderCfg {
        return sortHeaderCfg as SortHeaderCfg;
    }
}

@Component({
               selector: '...',
           })
export class MyViewComponent {

    MyEntityNameOf: (name: keyof MyEntity) => keyof MyEntity = MyEntity.nameOf;
    SortCfg = SortCfg;
    // ...
}
```
