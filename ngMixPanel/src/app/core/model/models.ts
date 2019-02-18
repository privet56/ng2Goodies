export interface IBaseItem
{
    bScore:number;
    bLink:string;
    bTitle:string;
}
export class SearchResultItem implements IBaseItem
{
    answer_count: number;
    closed_date: number;
    closed_reason: string;
    creation_date: number;
    is_answered: boolean;
    last_activity_date: number;
    tags: Array<string>;
    view_count: number;
    link:string;
    score:number;
    title:string;

    get bTitle():string {return this.title;}
    get bLink():string {return this.link;}
    get bScore():number {return this.score;}

}
export class WeatherDataItem implements IBaseItem
{
    Datum: string;
    Zeit: string;
    Regen: number;
    Wind: number;
    Richtung: number;
    Helligkeit: number;
    answer_count:number;

    get bTitle():string {return "Weather at " + this.Datum+" - "+this.Zeit+": Wind strength: "+this.Wind;}
    get bLink():string {return "http://www.openweathermap.com/city.name=munich&date="+this.Datum+"&time="+this.Zeit;}
    get bScore():number {return this.Wind;}
}
