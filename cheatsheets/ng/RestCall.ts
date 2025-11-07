import {computed, effect, Signal, signal, WritableSignal} from '@angular/core';
import {Observable} from 'rxjs';


export class RestCall<T> {

    public static isValueSet(o: any): boolean {
        return (o != null); // juggling comparison checks for null *and* undefined in one go
    }

    defaultErrorText: string = 'An error occured';

    value: WritableSignal<T> = signal<T>(null);
    error: WritableSignal<string> = signal<string>(null);
    loading: WritableSignal<boolean> = signal<boolean>(false);

    /**
     * call it within an injection context(component-constructor|runInInjectionContext)!
     */
    constructor(defaultErrorText: string) {

        if (RestCall.isValueSet(defaultErrorText)) {
            this.defaultErrorText = defaultErrorText;
        }

        effect(() => {
            if (this.loading()) {
                this.value.set(null);
            }
        }, {allowSignalWrites: true});
    }

    /**
     * doesn't check for this.loading()!, just for having a value or an error!
     */
    called: Signal<boolean> = computed(() => {
        // noinspection RedundantIfStatementJS
        if (RestCall.isValueSet(this.value()) ||
            RestCall.isValueSet(this.error())) {
            return true;
        }
        return false;
    });

    call(fun: () => Observable<T>, onDone: (result: T | null, error: any | null, errorText: string | null) => void): void {

        this.loading.set(true);
        this.value.set(null);
        this.error.set(null);

        fun().subscribe({
                            next: (value: T) => {
                                this.value.set(value);
                                if (onDone) {
                                    onDone(this.value(), null, null);
                                }
                            },
                            error: (error: any) => {
                                this.error.set(error.text ?? this.defaultErrorText);
                                if (onDone) {
                                    onDone(null, error, this.error());
                                }
                            },
                            complete: () => {
                                this.loading.set(false);
                            }
                        });
    }
}
