# Advanced Ng / JavaScript / Styling issues

## 1. How to broadcast messages/events?
### 1.1. broadcast:
```js
this.elementRef.nativeElement.dispatchEvent(new CustomEvent("myCustomEvent", { bubbles: true, detail: new MyData() }));
```
### 1.2. listen:
 (somewhere in the parent chain)
```html
<div (myCustomEvent)="onMyCustomEvent($event)">...</div>
```
```js
onMyCustomEvent($event: CustomEvent<MyData>): void {
    myData: MyData = $event.detail;
}
```

## 2. How to speed up very very long not-lazy-loaded lists?
Answer: render the elements of the list only if they are visible!
```html
<div *ngIf="visible$ | async">...the DOM of my very complicated list element...</div>
```
```js
export class AMyComponent implements AfterViewInit, OnDestroy {
    private visibilityObserver: IntersectionObserver;
    public visible$: Observable<boolean>;
    private visibleSubject = new BehaviorSubject<boolean>(false);

    constructor(private element: ElementRef) {
        this.visible$ = this.visibleSubject.asObservable();
    }
    ngAfterViewInit(): void {
        this.visibilityObserver = new IntersectionObserver(
            (entries: IntersectionObserverEntry[]) => {
                const visible: boolean = entries[0].isIntersecting;
                this.visibleSubject.next(visible);
            });
        this.visibilityObserver.observe(this.element.nativeElement);
    }

    ngOnDestroy(): void {
        this.visibilityObserver.disconnect();
    }
}
```
## 3. How to style the triangle of a tooltip component?
```css
.tooltip {
    width: 300px;
    margin-top: 8px;
    margin-left: -150px; /* Use half of the width (120/2 = 60), to center the tooltip */
    background-color: $white;
    color: $gunmetal;
    text-align: center;
    border: 2px solid $cloudy-blue;
    padding: 5px 0;
    position: absolute;
    top: 0px;
    z-index: $zindex-modal;
}
/*triangle on top-middle of the tooltip*/
.tooltip::after {
    content: "";
    position: absolute;
    bottom: 100%;
    left: 49%;
    margin-left: -5px;
    border-width: 10px;
    border-style: solid;
    border-color: transparent transparent lightgray transparent;
}
```
### 3.1. ...and, how to position the tooltip?
```js
export class TooltipComponent implements AfterViewInit {

    @ViewChild("tooltip", { static: false })
    private tooltipElement: ElementRef;

    ...

    ngAfterViewInit(): void {
        //append tooltip to root, so that mouse positions (pageY & pageX) are relative to the page
        document.getElementsByTagName("body")[0].appendChild(this.tooltipElement.nativeElement);
    }
    getTop(): string {
        return this.mouseEvent.pageY + "px";
    }
    getLeft(): string {
        return this.mouseEvent.pageX + "px";
    }
```
```html
<div class="tooltiptext tooltip" #tooltip
    [style.display]="showMe() ? 'block' : 'none'"
    [style.top]="getTop()" [style.left]="getLeft()"
    (mouseover)="onMouseOver($event, true)" (mouseout)="onMouseOver($event, false)">
        ...content of the tooltip...
</div>
```
