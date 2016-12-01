/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { PersistentRouterOutlet } from './PersistentRouterOutlet';
import { RouterOutletMap } from '@angular/router/src/router_outlet_map';
import { CanDeactivate, RouterOutlet, Router, Routes } from '@angular/router';
import { OpaqueToken, ComponentFactoryResolver, EventEmitter, Injector, OnDestroy, ResolvedReflectiveProvider, ViewContainerRef, NgModuleFactoryLoader, Compiler } from '@angular/core';

describe('Component: PersistentRouterOutlet', () =>
{
  let persistentRouterOutlet : PersistentRouterOutlet = null;

  beforeEach(() =>
  {
    //...use DI...
    TestBed.configureTestingModule({
      providers: [
        PersistentRouterOutlet,                                   //the class to be tested and...
        RouterOutletMap,                                          // it's constr arg 1
        ViewContainerRef,                                         // it's constr arg 2
        ComponentFactoryResolver,                                 // it's constr arg 3
        { provide: 'name', useValue: 'name' },                    // it's constr arg 4
        { provide: Router, useValue: null }                       // it's constr arg 5      useValue/useClass
      ]
    });

    //...or create object to be tested manually
    persistentRouterOutlet = new PersistentRouterOutlet(new RouterOutletMap(), null, null, null, null);
  });

//test class with DI-created object
  it('should inject a _persistentRouterOutlet instance',
    inject([PersistentRouterOutlet], (_persistentRouterOutlet: PersistentRouterOutlet) =>
  {
    expect(_persistentRouterOutlet).toBeTruthy();
  }));

//test class with the manually created object
  it('should create a persistentRouterOutlet instance', () =>
  {
    expect(persistentRouterOutlet).toBeTruthy();
  });
  it('should not cache complicated urls', () =>
  {
    let url:string = "/complicated/Url?param=12";
    let isCacheable:boolean = persistentRouterOutlet.isCacheable(url);
    expect(isCacheable).toEqual(false);
  });
  it('should cache simple urls', () =>
  {
    let url:string = "search";
    let isCacheable:boolean = persistentRouterOutlet.isCacheable(url);
    expect(isCacheable).toEqual(true);
  });

});
