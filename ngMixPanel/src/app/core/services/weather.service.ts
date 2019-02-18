import { Injectable } from '@angular/core';
import {Http, Response} from "@angular/http";
import {Observable} from "rxjs";
import { IBaseItem, WeatherDataItem } from '../model/models';

@Injectable()
export class WeatherService
{
      constructor(private http: Http)
      {
  
      }

      public search(): Observable<Array<IBaseItem>>
      {
          return this.http.get("data/weatherdata.json")
              .map((res: Response) => {
                let data = res.json();
                //var s = JSON.stringify(data);
                //alert("WEATHERDATA:"+s);
                //return WeatherService.map(data["items"]);
                let a:Array<IBaseItem> = (data["items"] as Array<IBaseItem>).map(e => Object.assign(new WeatherDataItem(), e));
                return a;
              })
              .catch((err: Response) => Observable.of(err.json()));
      }
      public static map(a:Array<JSON>):Array<IBaseItem>
      {
        return a.map(e => Object.assign(new WeatherDataItem(), e));
        /*alternative, longer implementation:
        let b:Array<IBaseItem> = new Array<WeatherDataItem>();
        a.forEach(e => {
            b.push(Object.assign(new WeatherDataItem(), e));
        });
        return b;
        */
      }  
  }
  