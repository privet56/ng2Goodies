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
