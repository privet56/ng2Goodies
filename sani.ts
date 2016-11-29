import {Pipe} from '@angular/core';
import { DomSanitizer, SafeResourceUrl, SafeUrl, SafeHtml } from '@angular/platform-browser';

@Pipe({
    name: 'sani'
})

export class SaniPipe
{
   constructor(private _sanitizer: DomSanitizer)
   {

   }

  transform(value: string, limit : number) : SafeHtml
  {
    if(!value)return value;
    return this._sanitizer.bypassSecurityTrustHtml(value);
  }
} 
