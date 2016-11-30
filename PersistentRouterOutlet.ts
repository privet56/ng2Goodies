

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
  public static __LASTRESOLVEDURL : string = "__resolvedurl";
  public static __MAX2LOG : number  = 33;  
  protected LOGGED : number         = 0;
  private cache = [];
  private location_: ViewContainerRef;

  constructor(parentOutletMap: RouterOutletMap, location: ViewContainerRef, resolver: ComponentFactoryResolver, name: string,
              @Inject(Router) _parentRouter: Router)
  {
      super(parentOutletMap, location, resolver, name);
      this.location_ = location;
      /*
      this.activateEvents.subscribe((activatedInstance) =>
      {
       this.activatedInstance = activatedInstance;
      });
      */
  }
  activate( activatedRoute: ActivatedRoute,
            resolver: ComponentFactoryResolver,
            injector: Injector,
            providers: ResolvedReflectiveProvider[],
            outletMap: RouterOutletMap): void
  {
    //activatedRoute.url is a BehaviorSubject    
    activatedRoute.url.subscribe(res =>
    {
        if (res != null && res.length > 0)
        {
            let url: string = res[0].path;
            activatedRoute[PersistentRouterOutlet.__LASTRESOLVEDURL] = url;

            if(this.getActivatedRoute() && (url === this.getActivatedRoute()[PersistentRouterOutlet.__LASTRESOLVEDURL]))
            {
                this.log("no change in url '"+this.getActivatedRoute()[PersistentRouterOutlet.__LASTRESOLVEDURL]+"'");
                return;
            }

            let oldActivated:any = this.getActivated();
            let newActivated:any = this.cache[url];

            if(!newActivated)
            {   //let super handle it and cache result
                super.activate(activatedRoute, resolver, injector, providers, outletMap);
                this.cache[url] = this.getActivated();
                this.log("FIRST: '"+url+"' changeDet:"+this.getActivated().changeDetectorRef);
            }
            else
            {   //detach current and attach from cache
                if(oldActivated)
                {
                    let i:number = this.location_.indexOf(oldActivated.changeDetectorRef._view.ref);
                    this.log("DEACTIVATED("+i+"): changeDetViewRef:"+oldActivated.changeDetectorRef._view.ref);
                    this.location_.detach(i);
                }
                this.outletMap = outletMap;
                this.setActivatedRoute(activatedRoute);
                this.setActivated(newActivated);
                this.log("CACHE: "+url);
                this.location_.insert(newActivated.changeDetectorRef._view.ref);
                //activated.changeDetectorRef.detectChanges();  //do not call, as future is already resolved
                this.activateEvents.emit(this.getActivated().instance);
            }
        }
        else
        {
            this.log("ERR: !url res:"+res);
        }
    });
  }
  deactivate(): void
  {
    //don't call super, because super destroy()'s

    if (this.getActivated())
    {
        var c = this.component;
        let i:number = this.location_.indexOf(this.getActivated().changeDetectorRef._view.ref);
        this.log("deactivate()DEACTIVATED("+i+"): changeDetViewRef:"+this.getActivated().changeDetectorRef._view.ref);
        this.location_.detach(i);
        //this.activated.destroy();     //this is what supper does
        this.setActivated(null);
        this.deactivateEvents.emit(c);
    }
  }

  //getter/setter for private members of super
  protected getActivated()
  {
      return this.activated;
  }
  protected setActivated(activated:any) : void
  {
      this.activated = activated;
  }
  protected getActivatedRoute()
  {
      return this._activatedRoute;
  }
  protected setActivatedRoute(activatedRoute:any) : void
  {
      this._activatedRoute = activatedRoute;
  }
  
  public log(s:string, o?:any) : void
  {
      if(this.LOGGED++ > PersistentRouterOutlet.__MAX2LOG)
      {
          return;   //don't log too much, but do it at the beginning (and so 'force' to look for the official solution)
      }
      console.log(""+this.LOGGED+": router.activate:"+s);
  }
}
