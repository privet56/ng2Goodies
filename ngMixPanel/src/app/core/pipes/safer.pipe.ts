import { Pipe, PipeTransform } from '@angular/core';
import { DomSanitizer } from "@angular/platform-browser";

@Pipe({
  name: 'safer'
})
export class SaferPipe implements PipeTransform
{
  constructor(private sanitized: DomSanitizer)
  {
  }

  transform(value: string)
  {
      return this.sanitized.bypassSecurityTrustHtml(value);
  }
}
