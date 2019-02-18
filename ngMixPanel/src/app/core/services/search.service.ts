import {Injectable} from "@angular/core";
import {Http, Response} from "@angular/http";
import {Observable} from "rxjs";
import { IBaseItem, SearchResultItem } from "../model/models";

@Injectable()
export class SearchService
{
    private static readonly apiUrl =
        "https://api.stackexchange.com/2.2/search?pagesize=20&order=desc&sort=activity&site=stackoverflow&intitle=";

    constructor(private http: Http)
    {

    }

    search(keyword: string): Observable<Array<IBaseItem>>
    {
        return this.http.get(SearchService.apiUrl + keyword)
            .map((res: Response) => {
                let data = res.json();
                console.log("API USAGE: " + data.quota_remaining + " of " + data.quota_max + " requests available\n" );
                /*
                console.log("------------------------");
                console.log(data);
                var s = JSON.stringify(data);
                var win = window.open("", "Title", "toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=yes,width=780,height=200,top="+(screen.height-400)+",left="+(screen.width-840));
                win.document.body.innerHTML = s;
                console.log("------------------------");
                */
                return SearchService.map(data["items"]);
            })
            .catch((err: Response) => Observable.of(err.json()));
    }
    public static map(a:Array<JSON>):Array<IBaseItem>
    {
        return a.map(e => Object.assign(new SearchResultItem(), e));
        
        /*alternative, longer implementation:
        let b:Array<IBaseItem> = new Array<SearchResultItem>();
        a.forEach(e => {
            b.push(Object.assign(new SearchResultItem(), e));
        });
        return b;
        */
    }
}
