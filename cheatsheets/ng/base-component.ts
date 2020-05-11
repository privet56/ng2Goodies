import {OnDestroy} from "@angular/core";
import {Subscription} from "rxjs";

export class BaseComponent implements OnDestroy {

    protected subscriptions: Subscription[] = [];

    constructor() {

        // ensure 'ngOnDestroy' is called anyway, independently of the child class implementation; based on
        // https://stackoverflow.com/questions/54979862/ensure-super-ondestroy-in-derived-component#56303624 and
        // https://stacksandfoundations.wordpress.com/2016/06/24/using-class-inheritance-to-hook-to-angular2-component-lifecycle/

        const ngOnDestroyRef = this.ngOnDestroy;

        this.ngOnDestroy = () => {
            ngOnDestroyRef.call(this);
            this.unsubscribeAll();
        };
    }

    ngOnDestroy(): void {
        this.unsubscribeAll();
    }

    protected unsubscribeAll(): void {
        if (this.subscriptions) {
            this.subscriptions.forEach(subscription => subscription.unsubscribe());
            this.subscriptions.length = 0;
        }
    }
}
