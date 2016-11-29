import { XDom, nodeTypes } from './xdom';
//import nodeTypes = XDom.nodeTypes;

export class xdom2jso
{
    localName:boolean = false;

    constructor(localName:boolean)
    {
        this.localName = localName;
    }

    convert(xmlRoot:Node, localName?:boolean):{}
    {
        if (undefined !== localName) this.localName = localName;

        var jsoRoot:{} = {};
        this.convertNodes(jsoRoot, xmlRoot);
        return jsoRoot;
    }

    convertNodes(jso:any, node:Node)
    {
        var nodeType:number = node.nodeType;

        if (nodeTypes.ELEMENT === nodeType)
        {
            var nodeName:string = this.localName ? node.localName : node.nodeName;

            var jsoNode:any = {};

            var attributeNodes:NamedNodeMap = node.attributes;
            var attributeIndex:number = attributeNodes.length;

            if (0 < attributeIndex)
            {
                var attributes:any = {};

                for (var attributeIndex:number = 0; attributeNodes.length > attributeIndex; ++attributeIndex)
                {
                    var attribute:Attr = attributeNodes.item(attributeIndex);
                    attributes[this.localName ? attribute.localName : attribute.nodeName] = attribute.value;
                }

                jsoNode['_'] = attributes;
            }

            var childNodes:NodeList = node.childNodes;

            for (var childIndex:number = 0; childNodes.length > childIndex; ++childIndex)
            {
                this.convertNodes(jsoNode, childNodes[childIndex]);
            }

            if (undefined === jso[nodeName])
            {
                jso[nodeName] = jsoNode;
            }
            else
            {
                if (Array !== jso[nodeName].constructor)
                {
                    var jsoFirstNode:{} = jso[nodeName];

                    jso[nodeName] = [];
                    jso[nodeName].push(jsoFirstNode);
                }

                jso[nodeName].push(jsoNode);
            }
        }
        else if (nodeTypes.TEXT === nodeType)
        {
            var nodeValue:string = node.nodeValue;

            if (/\S/.test(nodeValue))
            {
                jso['$'] = nodeValue.trim();
            }
        }
    }
}
