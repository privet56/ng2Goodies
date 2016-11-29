import { Injectable, EventEmitter } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';

export class UHtmlUtil
{
    //ü = 65533
    protected static rxEmail : RegExp = new RegExp('(\\S+)@(\\S+)', "g");
    protected static rxLink = new RegExp('(\\s)http(\\S+)', "g");
    protected static ue : string = String.fromCharCode(65533);
    protected static ueFound : number = 0;

    constructor()
    {
        
    }

    public static isNummericString(s:string, exceptions:string, trim:boolean) : boolean
    {
        if((s == null) || (s == undefined) || ((typeof s) !== 'string') || (s === ''))
        {
            return false;
        }
        if(trim)
        {
            s = s.trim();
        }
        for(let i:number=0;i<s.length;i++)
        {
            let c:string = s.charAt(i);
            let isNum:boolean = c >= '0' && c <= '9';
            if(!isNum && (exceptions.indexOf(c) > -1))
                continue;
            if(!isNum)
                return false;
        }
        return true;
    }

    public static entitifyObj(o : any) : any
    {
        if((typeof o) === 'string')
        {
            return UHtmlUtil.entitify(o);
        }
        for(let prop in o)
        {
            let propVal:any = o[prop];
            if(!propVal)
            {
                o[prop] = ""; 
            }
            else if((typeof propVal) === 'object')
            {
                UHtmlUtil.entitifyObj(propVal);
            }
            else if((typeof propVal) === 'string')
            {
                o[prop] = UHtmlUtil.entitify(propVal);
            }
        }
        return o;
    }
    public static entitify(s : string) : string
    {
        if(!s)return "";

        if(s.indexOf(UHtmlUtil.ue) > -1)
            console.log("ERR: ü coded wrongly!");
        /*temporary little fix
        while(s.indexOf(HtmlUtil.ue) > -1)
        {
            s = s.replace(HtmlUtil.ue, 'ü');
        }*/

        return UHtmlUtil.linkify(UHtmlUtil.emailify(s));
    }
    public static emailify(s : string) : string
    {
        if(s.indexOf("<a href='mailto:") > -1)
            return s;
        s = s.replace(UHtmlUtil.rxEmail, "<a href='mailto:$1@$2'>$1@$2</a>")
        return s;
    }
    public static linkify(s : string) : string
    {
        if(s.indexOf("<a href='http") > -1)
            return s;        
        s = s.replace(UHtmlUtil.rxLink, "$1<a href='http$2' target='_new'>http$2</a>")
        return s;
    }

    public static o2SearchXML(queryParts:Array<any>, sort:string, sortAsc: boolean, filter:{name:string,value:string}[]) : string
    {
        let getCondis = function(queryParts:Array<any>) : Set<string>
        {
            let condis : Set<string> = new Set<string>();
            for(let i:number=0;i<queryParts.length;i++)
                condis.add(queryParts[i].field);
            return condis;

        };
        let condis : Set<string> = getCondis(queryParts);
        var oParser = new DOMParser();
        var xmlDoc = oParser.parseFromString('<SearchRequest xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"></SearchRequest>', 'text/xml');
        var xmlDocRoot  = xmlDoc.getElementsByTagName("SearchRequest")[0];
        let condisCount : number = 0;
        condis.forEach(function(condi)
        {
            var xmlEleCondi = xmlDoc.createElement(condi);
            for(let i:number=0;i<queryParts.length;i++)
            {
                if(queryParts[i].field !== condi)continue;
                var xmlEleCheckFor = xmlDoc.createElement("CheckFor");
                xmlEleCheckFor.setAttribute("exclude", ""+queryParts[i].exclude);
                xmlEleCheckFor.appendChild(xmlDoc.createTextNode(queryParts[i].value));
                xmlEleCondi.appendChild(xmlEleCheckFor);
                condisCount++;
            }
            xmlDocRoot.appendChild(xmlEleCondi);
        });

        if(sort)
        {
            var xmlESortCondition = xmlDoc.createElement("SortCondition");
            {
                var xmlEAttributeName = xmlDoc.createElement("AttributeName");
                xmlEAttributeName.appendChild(xmlDoc.createTextNode(UHtmlUtil._getSortField(sort)));
                xmlESortCondition.appendChild(xmlEAttributeName);
            }
            {
                var xmlEAscending = xmlDoc.createElement("Ascending");
                xmlEAscending.appendChild(xmlDoc.createTextNode(sortAsc ? "1" : "0"));
                xmlESortCondition.appendChild(xmlEAscending);
            }
            xmlDocRoot.appendChild(xmlESortCondition);
        }
        if(filter && (filter.length > 0))
        {   //TODO: do I really have to list all possible filterFieldName's with empty value? 
            var xmlEFilterCondition = xmlDoc.createElement("FilterCondition");
            for(let i:number=0;i<filter.length;i++)
            {
                var xmlEfilterFieldName = xmlDoc.createElement(filter[i].name);
                xmlEfilterFieldName.appendChild(xmlDoc.createTextNode(filter[i].value));
                xmlEFilterCondition.appendChild(xmlEfilterFieldName);
            }
            xmlDocRoot.appendChild(xmlEFilterCondition);
        }

        if(condisCount < 1)
        {
            console.log("o2SearchXML ERR: !condisCount");
            console.log(queryParts);
        }

        var oSerializer = new XMLSerializer();
        var sXML = oSerializer.serializeToString(xmlDoc);
        return sXML;
    }

    private static _getSortField(fieldName : string)
    {   //TODO: how to do it better?
        if(fieldName.toLowerCase() == "title")                  return "CTitle";
        if(fieldName.toLowerCase() == "id")                     return "CId";
        if(fieldName.toLowerCase().indexOf('budget') > -1)      return "Budget";
        console.log("sortfield? field:'"+fieldName+"'");
        return fieldName;
    }
}
