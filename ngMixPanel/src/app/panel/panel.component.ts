import { Component, OnInit, Input } from '@angular/core';
import { SearchCachingService } from '../core/services/searchcaching.service';
import { PanelBaseComponent } from './panelbase.component';

@Component({
  selector: 'app-panel',
  templateUrl: './panel.component.html',
  styleUrls: ['./panel.component.scss']
})
export class PanelComponent extends PanelBaseComponent
{
  constructor(protected searchCachingService:SearchCachingService)
  {
    super(searchCachingService);
  }
}
