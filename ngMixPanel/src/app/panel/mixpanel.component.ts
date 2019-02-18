import { Component, OnInit, Input } from '@angular/core';
import { WeatherService } from '../core/services/weather.service';
import { SearchCachingService } from '../core/services/searchcaching.service';
import { PanelBaseComponent } from './panelbase.component';
import { IBaseItem, WeatherDataItem, SearchResultItem } from '../core/model/models';
import { Observable } from "rxjs";
import { map, zip, flatMap, concatAll, take, mergeMap, takeLast, combineAll } from 'rxjs/operators';

@Component({
  selector: 'app-mixpanel',
  templateUrl: './panel.component.html',
  styleUrls: ['./panel.component.scss']
})
export class MixpanelComponent extends PanelBaseComponent
{
  constructor(protected searchCachingService:SearchCachingService, protected weatherService:WeatherService)
  {
    super(searchCachingService);
  }
  protected load()
  {
   let r = Observable.
   forkJoin( this.searchCachingService.search(this.topic),
             this.weatherService.search())
   .pipe(map(([a1, a2]) => {

     let b1:Array<IBaseItem> = (a1 as Array<IBaseItem>).slice(0, 5);
     let b2:Array<IBaseItem> = (a2 as Array<IBaseItem>).slice(0, 5);
     let c:Array<IBaseItem> = b1.concat(b2);
     return this.shuffleArray(c);

   })).subscribe((re) => {
    this.newsList = re;
   });
  }
  protected shuffleArray(array:Array<IBaseItem>):Array<IBaseItem>
  {
    for (var i = array.length - 1; i > 0; i--)
    {
        var j = Math.floor(Math.random() * (i + 1));
        var temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    return array;
  }
}
