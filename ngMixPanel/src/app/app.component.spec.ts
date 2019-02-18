import { TestBed, async } from '@angular/core/testing';

import { AppComponent } from './app.component';
import {LayoutModule} from "./core/layout/layout.module";
import {DashboardComponent} from "./dashboard/dashboard.component";
import {SearchComponent} from "./search/search.component";
import {AppRoutingModule} from "./app.routing.module";
import {APP_BASE_HREF} from "@angular/common";
import {SearchService} from "./core/services/search.service";
import {WeatherService} from "./core/services/weather.service";
import {SearchCachingService} from "./core/services/searchcaching.service";
import {HttpModule} from "@angular/http";

describe('AppComponent', () => {
  beforeEach(async(() => {
    TestBed.configureTestingModule({
      imports: [
        LayoutModule,
        AppRoutingModule,
        HttpModule
      ],
      declarations: [
        AppComponent,
        DashboardComponent,
        SearchComponent
      ],
      providers: [
        {provide: APP_BASE_HREF, useValue: '/'},
        SearchService,
        SearchCachingService,
        WeatherService
      ]
    }).compileComponents();
  }));

  it('should create the app', async(() => {
    const fixture = TestBed.createComponent(AppComponent);
    const app = fixture.debugElement.componentInstance;
    expect(app).toBeTruthy();
  }));

});
