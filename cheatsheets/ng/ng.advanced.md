# Advanced Ng / JavaScript / Styling issues

## 1. How to broadcast messages/events?
### 1.1. broadcast:
```ts
this.elementRef.nativeElement.dispatchEvent(new CustomEvent("myCustomEvent", { bubbles: true, detail: new MyData() }));
```
### 1.2. listen:
 (somewhere in the parent chain)
```html
<div (myCustomEvent)="onMyCustomEvent($event)">...</div>
```
```ts
onMyCustomEvent($event: CustomEvent<MyData>): void {
    const myData: MyData = $event.detail;
    //... work with myData...
}
```

## 2. How to speed up very very long not-lazy-loaded lists?
Answer: render the elements of the list only if they are visible!
```html
<div *ngIf="visible$ | async">...the DOM of my very complicated list element...</div>
```
(...or in advanced, reusable cases you should work with &lt;ng-template)
```ts
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
&.tooltiptriangle-halfsquare--morning {
    > div {
      background-image: linear-gradient(
                      to top left,
                      $pale-grey 49%,
                      $bluish-grey 51%
      );
    }
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
### 3.1. ...and, how to position the tooltip within *nested* **scrollable** areas?
```ts
export class TooltipComponent implements AfterViewInit {

    @ViewChild("tooltip", { static: false })
    private tooltipElement: ElementRef;

    ...

    ngAfterViewInit(): void {
        //append tooltip to root, so that mouse positions (pageY & pageX) are relative to the page
        document.getElementsByTagName("body")[0].appendChild(this.tooltipElement.nativeElement);
    }
    getTop(): string {
        //return this.mouseEvent.pageY + "px";  //this line would position the tooltip to the mouse pos

        return this.absolutePosition(this.onMouseOverEvent.nativeElement).top +
                this.onMouseOverEvent.nativeElement.offsetHeight + "px";

    }
    getLeft(): string {
        //return this.mouseEvent.pageX + "px";  //this line would position the tooltip to the mouse pos
        return this.absolutePosition(this.onMouseOverEvent.nativeElement).left +
            (this.onMouseOverEvent.nativeElement.offsetWidth / 2) + "px";
    }
    protected absolutePosition(el) {
        let
            found,
            left = 0,
            top = 0,
            width = 0,
            height = 0,
            offsetBase = absolutePosition.offsetBase;

        if (!offsetBase && document.body) {
            offsetBase = absolutePosition.offsetBase = document.createElement('div');
            offsetBase.style.cssText = 'position:absolute;left:0;top:0';
            document.body.appendChild(offsetBase);
        }
        if (el && el.ownerDocument === document && 'getBoundingClientRect' in el && offsetBase) {
            let boundingRect = el.getBoundingClientRect();
            let baseRect = offsetBase.getBoundingClientRect();
            found = true;
            left = boundingRect.left - baseRect.left;
            top = boundingRect.top - baseRect.top;
            width = boundingRect.right - boundingRect.left;
            height = boundingRect.bottom - boundingRect.top;
        }
        return {
            found: found,
            left: left,
            top: top,
            width: width,
            height: height,
            right: left + width,
            bottom: top + height
        };
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
## 4. How to prevent a DIV from breaking to the next line?
```html
<div style="height:200px;width:500px;background-color:yellow;">
	<div style="height:200px;width:50px;background-color:lightcyan;float:left;">
		content on the left side (50px)
	</div>
	<!-- *has* to be before the overlong element! -->
	<div style="height:200px;width:50px;background-color:lightgreen;float:right;">
		content on the right side (50px)
	</div>
	<div style="height:30px;width:460px;background-color:lightblue;">
		<!-- overlong content in the middle (460px) -->
		<div style="width:100%;max-height:30px;background-color:red;overflow:hid_den;">
			<!-- these DIVs break to a new line -->
			<div style="height:30px;width:130px;background-color:lightgray;float:left;margin:7px;">1</div>
			<div style="height:30px;width:130px;background-color:lightgray;float:left;margin:7px;">2</div>
			<div style="height:30px;width:130px;background-color:lightgray;float:left;margin:7px;">3</div>
		</div>
	</div>
</div>
```
... or just use a &lt;table&gt; element...
