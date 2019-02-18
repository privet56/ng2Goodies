import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'trunc'
})
export class TruncPipe implements PipeTransform
{
  transform(value: string, limit:number) : string
  {
    let trail = '...';//could be a second arg...
    return value.length > limit ? value.substring(0, limit) + trail : value;
  }
}
