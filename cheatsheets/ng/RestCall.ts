import {computed, effect, Signal, signal, WritableSignal} from '@angular/core';
import {Observable} from 'rxjs';

export class RestCall<T> { // ~ similar to the future { resource } from '@angular/core';

    public static isValueSet(o: any): boolean {
        return (o != null); // juggling comparison checks for null *and* undefined in one go
    }

    protected defaultErrorText: string = 'An error occured.';

    protected _value: WritableSignal<T> = signal<T>(null);
    protected _error: WritableSignal<string> = signal<string>(null);
    protected _loading: WritableSignal<boolean> = signal<boolean>(false);

    public readonly value: Signal<T> = this._value.asReadonly();
    public readonly error: Signal<string> = this._error.asReadonly();
    public readonly loading: Signal<boolean> = this._loading.asReadonly();

    /**
     * call it within an injection context(component-constructor|runInInjectionContext)!
     */
    constructor(defaultErrorText: string|null) {

        if (RestCall.isValueSet(defaultErrorText)) {
            this.defaultErrorText = defaultErrorText as string;
        }

        effect(() => {
            if (this._loading()) {
                this._value.set(null);
            }
        }, {allowSignalWrites: true});
    }

    /**
     * doesn't check for this.loading()!, just for having a value or an error!
     */
    called: Signal<boolean> = computed(() => {
        // noinspection RedundantIfStatementJS
        if (RestCall.isValueSet(this._value()) ||
            RestCall.isValueSet(this._error())) {
            return true;
        }
        return false;
    });

    call(fun: () => Observable<T>, onDone: (result: T|null, error: Error|null, errorText: string|null) => void): void {

        this._loading.set(true);
        this._value.set(null);
        this._error.set(null);

        fun().subscribe({
                            next: (value: T) => {
                                this._value.set(value);
                                if (onDone) {
                                    onDone(this._value(), null, null);
                                }
                            },
                            error: (error: any) => {
                                this._error.set(error.text ?? this.defaultErrorText);
                                if (onDone) {
                                    onDone(null, error, this._error());
                                }
                            },
                            complete: () => {
                                this._loading.set(false);
                            }
                        });
    }
}
