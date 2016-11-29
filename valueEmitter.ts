import { Injectable, EventEmitter } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';

export class ValueEmitter<T> extends EventEmitter<T>
{
    private value : T = null;
    constructor(isAsync: boolean = false)
    {
        super(isAsync);
    }
    public getValue() : T
    {
        return this.value;
    }
    public emit(value : T) : void
    {
        this.value = value;
        super.emit(value);
    }
}
