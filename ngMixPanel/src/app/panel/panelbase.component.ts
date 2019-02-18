import { Component, OnInit, Input } from '@angular/core';
import { SearchCachingService } from '../core/services/searchcaching.service';
import { IBaseItem, SearchResultItem } from '../core/model/models';

@Component({
  templateUrl: './panel.component.html',
  styleUrls: ['./panel.component.scss']
})
export class PanelBaseComponent implements OnInit
{
  @Input("topic") topic:string;

  public newsList:Array<IBaseItem> = new Array<IBaseItem>();

  constructor(protected searchCachingService:SearchCachingService)
  {

  }

  ngOnInit()
  {
    this.load();
  }
  protected load()
  {
    this.searchCachingService.search(this.topic).subscribe((re) => {
      this.newsList = (re as Array<IBaseItem>).slice(0, 10);
    });
  }
  public getItemTitle(i:SearchResultItem):string {
    return i.bTitle;
  }
  public getItemLink(i:SearchResultItem):string {
    return i.bLink;
  }
  public getItemScore(i:SearchResultItem):number {
    return i.bScore;
  }
}
