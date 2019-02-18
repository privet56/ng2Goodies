import { TestBed, inject } from '@angular/core/testing';

import { SearchService } from './search.service';
import {HttpModule} from "@angular/http";
import {APP_BASE_HREF} from "@angular/common";

describe('SearchService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      imports: [HttpModule],
      providers: [
        SearchService
      ]
    });
  });

  it('should ...', inject([SearchService], (service: SearchService) => {
    expect(service).toBeTruthy();
  }));
});
