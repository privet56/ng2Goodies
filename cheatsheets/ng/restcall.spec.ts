import {fakeAsync, inject, tick} from '@angular/core/testing';
import {Injector, runInInjectionContext} from '@angular/core';
import {RestCall} from './restcall';
import {Observable, Subscriber} from 'rxjs';

describe('RestCall', () => {
    it('should maintain state', inject([Injector], fakeAsync((injector: Injector) => {

        runInInjectionContext(injector, () => {

            const restCall: RestCall<string> = new RestCall<string>(null);
            expect(restCall.loading()).toBe(false);
            let subscriber: Subscriber<string> = null;
            restCall.call(() => {
                return new Observable<string>((_subscriber: Subscriber<string>) => {
                    subscriber = _subscriber;
                    /* we could use setTimeout too, but that would need more tick()
                    setTimeout(() => {
                        subscriber.next('resultValue');
                        subscriber.complete();
                    }, 1); */
                });

            }, (result: string|null, error: Error|null, errorText: string|null): void => {
                expect(RestCall.isValueSet(result)).toBe(true);
                expect(RestCall.isValueSet(error)).toBe(false);
                expect(RestCall.isValueSet(errorText)).toBe(false);
            });

            expect(RestCall.isValueSet(restCall.value())).toBe(false);
            expect(RestCall.isValueSet(restCall.error())).toBe(false);
            expect(RestCall.isValueSet(restCall.loading())).toBe(true);
            expect(restCall.called()).toBe(false);

            const value = 'resultValue';
            subscriber.next(value);
            subscriber.complete();
            tick();

            expect(RestCall.isValueSet(restCall.error())).toBe(false);
            expect(restCall.value()).toBe(value);
            expect(restCall.loading()).toBe(false);
            expect(restCall.called()).toBe(true);
        });
    })));
});
