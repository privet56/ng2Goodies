import { Component } from '@angular/core';
import {SearchService} from "./core/services/search.service";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'app works!';

  constructor(private _searchService: SearchService) {

  }

  triggerService() {
    this._searchService.search("angular2").subscribe((res) => {
      console.log("API RESULT", res);
    });
  }

}
