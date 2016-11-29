
import { XDom, nodeTypes } from './xdom/xdom';
import { xdom2jso } from './xdom/xdom2jso';

export class SoapService
{
    private useGET : boolean = false;
    public debug;
    private asynchronous;
    private localName;
    private servicePort;
    private servicePath;
    private serviceUrl;
    private targetNamespace;

    private charset = "utf-8";   //better than iso-8859-1

    localNameMode: boolean;
    testMode: boolean;

    constructor(servicePort: string, servicePath: string, targetNamespace?: string, useGET? : boolean)
    {
        this.serviceUrl = servicePort + servicePath;
        this.targetNamespace = targetNamespace;
        this.asynchronous = true;
        if(useGET != undefined) this.useGET = useGET;
    }

    envelopeBuilder: (response: {}, method : string) => string;
    jsoResponseHandler: (response: {}) => void;
    xmlResponseHandler: (response: NodeListOf<Element>) => void;

    post(method: string, parameters: any, responseRoot?: string) : void
    {
        var _this = this;
        var request = this.toXml(parameters);
        var envelopedRequest = null != this.envelopeBuilder ? this.envelopeBuilder(request, method) : request;
        if (this.debug)
        {
            console.log('target namespace: ' + this.targetNamespace);
            console.log('method: ' + method+" (useGET:"+this.useGET+")");
            console.log('service URL: ' + this.serviceUrl);
            console.log('request: ' + request);
            console.log('envelopedRequest: ' + envelopedRequest);
            console.log((this.asynchronous ? 'asynchronous' : 'synchronous') + ' ' + (this.localName ? 'without namespaces' : 'with namespaces (if returned by the webservice)'));
        }
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.onreadystatechange = function ()
        {
            if (_this.debug)
            {
                console.log('XMLHttpRequest ready state: ' + xmlHttp.readyState);
            }
            if (4 == xmlHttp.readyState)
            {
                if (_this.debug)
                {
                    console.log('XMLHttpRequest status: ' + xmlHttp.status);
                    console.log('XMLHttpRequest status text: ' + xmlHttp.statusText);
                    console.log('XMLHttpRequest response headers: ' + xmlHttp.getAllResponseHeaders());
                }

                if(!xmlHttp.responseXML)
                {
                    let s : string = _this.serviceUrl+":"+method+"() "+xmlHttp.status+"="+xmlHttp.statusText+" REQUEST:"+envelopedRequest;
                    _this.jsoResponseHandler(new Error(s));
                    return;
                }

                var responseNodeList;

                if (!responseRoot)
                {
                    responseNodeList = xmlHttp.responseXML;
                }
                else
                {
                    responseNodeList = xmlHttp.responseXML.getElementsByTagNameNS('*', responseRoot);
                }

                if (null != _this.xmlResponseHandler)
                {
                    _this.xmlResponseHandler(responseNodeList);
                }
                if (null != _this.jsoResponseHandler)
                {
                    var response = (new xdom2jso(true/*useLocalNames(without namespace prefixes)*/)).convert(responseNodeList[0], _this.localName);
                    if (_this.debug)
                    {
                        console.log(JSON.stringify(response));
                    }

                    SoapService.jsonify(response, 0, null, null);
                    _this.jsoResponseHandler(response);
                }
            }
        };

        if(this.useGET)
        {
            xmlHttp.open("GET", this.serviceUrl, this.asynchronous);
            xmlHttp.setRequestHeader("SOAPAction", this.targetNamespace + '/' + encodeURIComponent(method));
            xmlHttp.setRequestHeader("Content-Type", "text/xml; charset="+this.charset);
            xmlHttp.send();
        }
        else
        {
            xmlHttp.open("POST", this.serviceUrl, this.asynchronous);
            //xmlHttp.withCredentials = true;
            xmlHttp.setRequestHeader("SOAPAction", this.targetNamespace + '/' + encodeURIComponent(method));
            xmlHttp.setRequestHeader("action", this.targetNamespace + '/' + encodeURIComponent(method));

            //not allowed to be set:
            //xmlHttp.setRequestHeader("Host", "localhost:3047");
            //xmlHttp.setRequestHeader("Accept-Encoding", "gzip,deflate");
            //xmlHttp.setRequestHeader("Connection", "Keep-Alive");
            //xmlHttp.setRequestHeader("User-Agent", "Apache");

            xmlHttp.setRequestHeader("Content-Type", "application/soap+xml;charset="+this.charset+";action=\""+this.targetNamespace + '/' + encodeURIComponent(method)+"\"");
            xmlHttp.send(envelopedRequest);
        }
    }
    private toXml(parameters)
    {
        var xml = "";
        var parameter;
        switch (typeof (parameters))
        {
            case "string":
                xml += parameters.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
                break;
            case "number":
            case "boolean":
                xml += parameters.toString();
                break;
            case "object":
                if (parameters.constructor.toString().indexOf("function Date()") > -1)
                {
                    var year = parameters.getFullYear().toString();
                    var month = ("0" + (parameters.getMonth() + 1).toString()).slice(-2);
                    var date = ("0" + parameters.getDate().toString()).slice(-2);
                    var hours = ("0" + parameters.getHours().toString()).slice(-2);
                    var minutes = ("0" + parameters.getMinutes().toString()).slice(-2);
                    var seconds = ("0" + parameters.getSeconds().toString()).slice(-2);
                    var milliseconds = parameters.getMilliseconds().toString();
                    var tzOffsetMinutes = Math.abs(parameters.getTimezoneOffset());
                    var tzOffsetHours = 0;
                    while (tzOffsetMinutes >= 60)
                    {
                        tzOffsetHours++;
                        tzOffsetMinutes -= 60;
                    }
                    var tzMinutes = ("0" + tzOffsetMinutes.toString()).slice(-2);
                    var tzHours = ("0" + tzOffsetHours.toString()).slice(-2);
                    var timezone = ((parameters.getTimezoneOffset() < 0) ? "-" : "+") + tzHours + ":" + tzMinutes;
                    xml += year + "-" + month + "-" + date + "T" + hours + ":" + minutes + ":" + seconds + "." + milliseconds + timezone;
                }
                else if (parameters.constructor.toString().indexOf("function Array()") > -1)
                {
                    for (parameter in parameters)
                    {
                        if (parameters.hasOwnProperty(parameter))
                        {
                            if (!isNaN(parameter))
                            {
                                (/function\s+(\w*)\s*\(/ig).exec(parameters[parameter].constructor.toString());
                                var type = RegExp.$1;
                                switch (type)
                                {
                                    case "":
                                        type = typeof (parameters[parameter]);
                                        break;
                                    case "String":
                                        type = "string";
                                        break;
                                    case "Number":
                                        type = "int";
                                        break;
                                    case "Boolean":
                                        type = "bool";
                                        break;
                                    case "Date":
                                        type = "DateTime";
                                        break;
                                }
                                xml += this.toElement(type, parameters[parameter]);
                            }
                            else
                            {
                                xml += this.toElement(parameter, parameters[parameter]);
                            }
                        }
                    }
                }
                else
                {
                    for (parameter in parameters)
                    {
                        if (parameters.hasOwnProperty(parameter))
                        {
                            xml += this.toElement(parameter, parameters[parameter]);
                        }
                    }
                }
                break;
            default:
                throw new Error("SoapService error: type '" + typeof (parameters) + "' is not supported");
        }
        return xml;
    }
    private toElement(tagNamePotentiallyWithAttributes, parameters)
    {
        var elementContent = this.toXml(parameters);
        /*if ("" == elementContent)
        {
            return "<" + tagNamePotentiallyWithAttributes + "/>";
        }
        else*/
        {
            return "<" + tagNamePotentiallyWithAttributes + ">" + elementContent + "</" + SoapService.stripTagAttributes(tagNamePotentiallyWithAttributes) + ">";
        }
    }
    private static stripTagAttributes(tagNamePotentiallyWithAttributes)
    {
        tagNamePotentiallyWithAttributes = tagNamePotentiallyWithAttributes + ' ';
        return tagNamePotentiallyWithAttributes.slice(0, tagNamePotentiallyWithAttributes.indexOf(' '));
    }
    /*
    A VERY DOMAIN SPECIFIC FUNCTION!
	use it if you call .NET WebServices!
    */
    private static jsonify(o: any, recDepth:number, parent:any, propNameInParent:any) : number
    {
        if(recDepth > 99)
        {
            console.log("SoapService:jsonify ERR: too deep recursion ("+recDepth+") for "+o+" ");
            console.log(o);
            return 0;
        }
        let propNr:number = -1;
        let hasNil:boolean = false;
        for(let prop in o)
        {
            propNr++;
            let propVal:any = o[prop];
            let childrenCount:number = 0;
            let isObject:boolean = ((typeof propVal) === 'object');
            if(isObject)
            {
                childrenCount = SoapService.jsonify(propVal, recDepth+1, o, prop);
            }
            if((prop == "nil") && (propVal == "true"))
            {
                hasNil = true;
            }
            if(prop == '_' && (childrenCount < 1) && isObject && (propVal["nil"] == "true"))
            {
                hasNil = true;
            }
        }
        {
            if((propNr < 1) && (o.$))
            {   //eg:   <CTypeID>11000</CTypeID>
                parent[propNameInParent] = ""+o.$;          //if(!parent)->letItCrash!
            }
            else if((propNr < 1) && parent && hasNil)
            {   //eg:   <Acronym i:nil="true"/>
                //eg:   <SBudget i:nil="true"></SBudget>
                parent[propNameInParent] = null;
            }
            else if((propNr < 0) && parent)
            {   //eg:   <Attachments />
                parent[propNameInParent] = null;
            }
            else if(hasNil)
            {
                console.log("SoapService:jsonify WRN: hasNil:"+hasNil+" propNr:"+propNr+" parent:"+parent+" propNameInParent:"+propNameInParent);
            }
        }
        return propNr;
    }
}
