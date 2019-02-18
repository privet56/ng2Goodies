import { Injectable } from '@angular/core';
import {Http, Response} from "@angular/http";
import {Observable} from "rxjs";
import {SearchService} from "./search.service";
import { IBaseItem } from '../model/models';

@Injectable()
export class SearchCachingService
{
      constructor(private http: Http, protected searchService:SearchService)
      {
  
      }
  
      search(keyword: string): Observable<Array<IBaseItem>>
      {
          return this.http.get("data/"+keyword+".json")
              .map((res: Response) => {
                  let data = res.json();
                  return SearchService.map(data["items"]);
              })
              .catch((err: Response) => {
                return this.searchService.search(keyword);
              });
      }
  }
  