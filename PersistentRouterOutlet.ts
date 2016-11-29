

import { Location } from '@angular/common';
import { NavigationExtras } from '@angular/router';
import {isBlank, isPresent} from '@angular/common/src/facade/lang';
import {StringMapWrapper} from '@angular/common/src/facade/collection';
import { ElementRef, Directive, ComponentRef, Attribute, Type, Inject, Component } from '@angular/core';
import { CanDeactivate, RouterOutlet, Router, Routes } from '@angular/router';
import { ComponentFactoryResolver, EventEmitter, Injector, OnDestroy, ResolvedReflectiveProvider, ViewContainerRef, NgModuleFactoryLoader, Compiler } from '@angular/core';
import { RouterOutletMap } from '@angular/router/src/router_outlet_map';
import { ActivatedRoute } from '@angular/router/src/router_state';
import { UrlSerializer, UrlTree } from '@angular/router/src/url_tree';
import { BehaviorSubject } from "rxjs/BehaviorSubject";

interface CacheItem {
    componentRef: ComponentRef<any>;
    reusedRoute: PageRoute;
    outletMap: RouterOutletMap;
    loaderRef?: ComponentRef<any>;
}

export class PageRoute {
    activatedRoute: BehaviorSubject<ActivatedRoute>;
    constructor(startRoute: ActivatedRoute) {
        this.activatedRoute = new BehaviorSubject(startRoute);
    }
}

/**
 * Reference Cache
 */
class RefCache {
    private cache: Array<CacheItem> = new Array<CacheItem>();

    public push(
        componentRef: ComponentRef<any>,
        reusedRoute: PageRoute,
        outletMap: RouterOutletMap,
        loaderRef: ComponentRef<any>) {
        this.cache.push({ componentRef, reusedRoute, outletMap, loaderRef });
    }

    public pop(): CacheItem {
        return this.cache.pop();
    }

    public peek(): CacheItem {
        return this.cache[this.cache.length - 1];
    }

    public get length(): number {
        return this.cache.length;
    }
}

//TODO: remove this class after an official ng2 persistentRouter is available!!!

@Component({
    selector: "persistent-router-outlet"
})
export class PersistentRouterOutlet extends RouterOutlet
{
  private cache = [];
  private location_: ViewContainerRef;

  constructor(parentOutletMap: RouterOutletMap, location: ViewContainerRef, resolver: ComponentFactoryResolver, name: string,
              @Inject(Router) _parentRouter: Router)
  {
      super(parentOutletMap, location, resolver, name);
      this.location_ = location;
  }
  activate( activatedRoute: ActivatedRoute,
            resolver: ComponentFactoryResolver,
            injector: Injector,
            providers: ResolvedReflectiveProvider[],
            outletMap: RouterOutletMap): void
  {
    //activatedRoute.url is a BehaviorSubject
    let url: string = activatedRoute.url._value[0].path;
      let oldActivated:any = this.getActivated();
      let activated:any = this.cache[url];
      if(!activated)
      {
        super.activate(activatedRoute, resolver, injector, providers, outletMap);
		this.cache[url] = this.getActivated();
		this.log("router.activate FIRST: "+url);
		this.log(this.getActivated().changeDetectorRef);
      }
      else
      {
        if(oldActivated)
        {
            let i:number = this.location_.indexOf(oldActivated.changeDetectorRef._view.ref);
            this.log("router.DEACTIVATED("+i+"): "+oldActivated.changeDetectorRef._view.ref);
            this.location_.detach(i);
        }
        this.outletMap = outletMap;
        this._activatedRoute = activatedRoute;
        this.setActivated(activated);
        this.log("router.activate CACHE: "+url);
        this.location_.insert(activated.changeDetectorRef._view.ref);
        //activated.changeDetectorRef.detectChanges();
        this.activateEvents.emit(this.getActivated().instance);
      }
  }
  deactivate(): void
  {
    //don't call super

    if (this.getActivated())
    {
        var c = this.component;
        let i:number = this.location_.indexOf(this.getActivated().changeDetectorRef._view.ref);
        this.log("router.DEACTIVATED("+i+"): "+this.getActivated().changeDetectorRef._view.ref);
        this.location_.detach(i);
        //this.activated.destroy();     //this is what supper does
        this.setActivated(null);
        this.deactivateEvents.emit(c);
    }
  }
  getActivated()
  {
      return this.activated;
  }
  setActivated(activated:any) : void
  {
      this.activated = activated;
  }
  
  log(s:any) : void
  {
      console.log(s);
  }
}
