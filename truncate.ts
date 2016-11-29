import {Pipe} from '@angular/core';

@Pipe({
  name: 'truncate'
})
export class TruncatePipe
{
  transform(value: string, limit : number) : string
  {
    if(!value)return value;
    let trail : string =  '...';	//TODO: make it configurable
    return value.length > limit ? value.substring(0, limit) + trail : value;
  }
}
