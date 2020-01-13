import {BehaviorSubject, Observable, Subject} from "rxjs";

export class ObservableSubject<T> {

    protected observable$: Observable<T> = null;
    protected value: T = null;

    public static BehaviorObservableSubject<T>(value: T): ObservableSubject<T> {
        return new ObservableSubject(new BehaviorSubject<T>(value));
    }

    constructor(protected subject: Subject<T>) {
        this.observable$ = subject.asObservable();
    }

    public asObservable(): Observable<T> {
        return this.observable$;
    }

    public setObservable(observable$: Observable<T>): Observable<T> {
        this.observable$ = observable$;
        return this.observable$;
    }

    public next(value: T) {
        this.value = value;
        this.subject.next(value);
    }

    public getValue(): T {
        return this.value;
    }
}

/*  conventional rx code sequence using 2 member variables:

    protected showMeSubject: Subject<boolean> = new BehaviorSubject<boolean>(false);
    protected showMeObservable$: Observable<boolean> = null;

    constructor() {
        this.showMeObservable$ = this.showMeSubject.asObservable();
    }
    ...
	this.showMeSubject.next(show);
	...
	[style.display]="(showMeObservable$ | async) ? 'block' : 'none'"
	...
	//get current value: ?
*/

/* code sequence using ObservableSubject<T>:

    protected showMeObservableSubject: ObservableSubject<boolean> = ObservableSubject.BehaviorObservableSubject(false);
    ...
    this.showMeObservableSubject.next(show);
    ...
    [style.display]="(showMeObservableSubject.asObservable() | async) ? 'block' : 'none'"
    ...
    const b: boolean = this.showMeObservableSubject.getValue();
*/
