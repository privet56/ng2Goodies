import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';

import { AppComponent } from './app.component';
import {SearchService} from "./core/services/search.service";
import {WeatherService} from "./core/services/weather.service";
import { SearchCachingService } from "./core/services/searchcaching.service";
import {AppRoutingModule} from "./app.routing.module";
import { DashboardComponent } from './dashboard/dashboard.component';
import {LayoutModule} from "./core/layout/layout.module";
import { SearchComponent } from './search/search.component';
import { PanelComponent } from './panel/panel.component';
import { TruncPipe } from './core/pipes/trunc.pipe';
import { SaferPipe } from './core/pipes/safer.pipe';
import { MixpanelComponent } from './panel/mixpanel.component';

@NgModule({
  declarations: [
    AppComponent,
    DashboardComponent,
    SearchComponent,
    PanelComponent,
    TruncPipe,
    SaferPipe,
    MixpanelComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule,

    LayoutModule,
    AppRoutingModule
  ],
  providers: [SearchService, SearchCachingService, WeatherService],
  bootstrap: [AppComponent]
})
export class AppModule { }
