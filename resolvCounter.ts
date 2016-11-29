
export class ResolvCounter
{
    private allItems2BeResolved : number = 0;
    private alreadyResolvedItems : number = 0;
    private start : number = new Date().getTime();
    private onCompletion : (hitCount : number, timeInMs:number) => void;

    constructor(allItems2BeResolved : number, onCompletion : (hitCount : number, timeInMs:number) => void)
    {
        this.allItems2BeResolved = allItems2BeResolved;
        this.onCompletion = onCompletion;
    }
    public onResolved(index : number) : number
    {
        this.alreadyResolvedItems++;
        let still2BeResolved = this.allItems2BeResolved - this.alreadyResolvedItems;
        if (still2BeResolved < 1)
        {
            this.onAllResolved();
        }
        return still2BeResolved;
    }
    public onAllResolved() : void
    {
        let end : number = new Date().getTime();
        let diff_ms : number = end - this.start;
        let diff_sec : number = Math.floor(diff_ms / 1000);
        console.log("RESOLVED "+this.allItems2BeResolved+"(="+this.alreadyResolvedItems+") in "+diff_ms+" ms = "+diff_sec+" seconds.");
        this.onCompletion(this.allItems2BeResolved, diff_ms);
    }
}
