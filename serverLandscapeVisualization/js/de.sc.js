"use strict";

this.de = {};
de.sc = {};

de.sc.ERR = "ERR";
de.sc.WRN = "WRN";
de.sc.INF = "INF";

de.sc.XMLELEMENT_NODE = 1;
de.sc.XMLATTRIBUTE_NODE = 2;
de.sc.XMLTEXT_NODE = 3;

//coffee
var __hasProp = {}.hasOwnProperty;
var __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; };

de.sc.xml = function(sXml)
{
	this.collectXmlElesFromRoot = function(sEleName, a)
	{
		this.collectXmlEles(this.XML, sEleName, a);
	};
	this.collectXmlEles = function(xmlEle, sEleName, a)
	{
		sEleName = sEleName.toLowerCase();
		for(var i=0;i<xmlEle.childNodes.length;i++)
		{
			var sub = xmlEle.childNodes[i];
			if (sub.nodeType!=1)continue;
			if((sub.nodeName.toLowerCase() == sEleName) ||
			   (sub.nodeName.toLowerCase().indexOf(":"+sEleName) > 0))
			{
				a.push(sub);
			}
			else
			{
				this.collectXmlEles(sub, sEleName, a);
			}
		}
	};
	this.getXmlChild = function(item, sChildName)
	{
		if(!item || !item.childNodes)return null;
		sChildName = sChildName === null ? null : sChildName.toLowerCase();
		for(var i=0;i<item.childNodes.length;i++)
		{
			var sub = item.childNodes[i];
			if (sub.nodeType!=1)continue;
			if (sChildName === null)return sub;
			if (sub.nodeName.toLowerCase() == sChildName)
				return sub;
			if (sub.nodeName.toLowerCase().indexOf(":"+sChildName) > 0)
				return sub;
		}
		return null;
	};
	this.getChildren = function(item, bOnlyChildrenWithChildren)
	{
		var children = new Array();
		for(var i=0;i<item.childNodes.length;i++)
		{
			var sub = item.childNodes[i];
			if (sub.nodeType!=1)continue;
			if(bOnlyChildrenWithChildren)
			{
				var subChildren = this.getChildren(sub, false);
				if (subChildren.length < 1)continue;
			}
			children.push(sub);
		}
		return children;
	};
	this.getXmlAttr = function(item, sAttrName)
	{
		if(item === null)return null;
		sAttrName = sAttrName.toLowerCase();
		for(var i=0;i<item.attributes.length;i++)
		{
			if(item.attributes[i].name.toLowerCase() == sAttrName)
				return item.attributes[i].value;
		}
		return null;
	};
	this.getxml = function(s)
	{
		var xmlDoc = null;
		if(window.DOMParser)
		{
			var parser=new DOMParser();
			xmlDoc=parser.parseFromString(s,"text/xml");
		}
		else//ie
		{
			xmlDoc=new ActiveXObject("Microsoft.XMLDOM");
			xmlDoc.async="false";
			xmlDoc.loadXML(s);
		}
		return xmlDoc.documentElement;
	};
	this.getSubEleValue = function(item, sSubEleName)
	{
		sSubEleName = sSubEleName.toLowerCase();
		for(var i=0;i<item.childNodes.length;i++)
		{
			var sub = item.childNodes[i];
			if (sub.nodeType!=1)continue;
			if (sub.nodeName.toLowerCase() == sSubEleName)
			{
				return sub.childNodes[0].nodeValue;
			}
		}
		return null;		
	};
	this.XML = this.getxml(sXml);
};
de.sc.xml.getSubs = function(item, aLeafs, aBranches)
{
	for(var i=0;i<item.childNodes.length;i++)
	{
		var sub = item.childNodes[i];
		if (sub.nodeType!=1)continue;
		var bHasChildEle = false;
		for(var j=0;j<sub.childNodes.length;j++)
		{
			var subsub = sub.childNodes[j];
			if (subsub.nodeType!=1)continue;
			bHasChildEle = true;break;
		}
		if(bHasChildEle)
			aBranches.push(sub);
		else
			aLeafs.push(sub);
	}
	return aBranches.length + aLeafs.length;
};
de.sc.xml.isLeaf = function(item)
{
	for(var i=0;i<item.childNodes.length;i++)
	{
		var sub = item.childNodes[i];
		if (sub.nodeType!=1)continue;
		return false;
	}
	return true;
};
de.sc.xml.isBranch = function(item)
{
	for(var i=0;i<item.childNodes.length;i++)
	{
		var sub = item.childNodes[i];
		if (sub.nodeType!=1)continue;
		return true;
	}
	return false;
};
de.sc.geturlcontent = function(sUrl)
{
	var sUrlContent = null;
	$.ajax({
	  url: sUrl,
	  context:window.document,
	  async:false/*synchronous!*/,
	  success: function(data)
	  {
	  	sUrlContent = data;
	  	if(typeof sUrlContent === "object")	//hopefully xml
	  	{
	  		sUrlContent =  (new XMLSerializer()).serializeToString(sUrlContent);
	  	}
	  }
	});
	return sUrlContent;	
};
de.sc.isempty = function(s)
{
	if((s === null) || (s === ""))return true;
	if($.trim(s) === "")return true;
	return false;
};
String.prototype.endsWith = function(suffix)
{
    return this.indexOf(suffix, this.length - suffix.length) !== -1;
};
String.prototype.upperFirst = function(bUpper)
{
    return (bUpper ? this.charAt(0).toUpperCase() : this.charAt(0).toLowerCase()) + this.slice(1);
};
String.prototype.e = function()
{
	var s = "";
	for(var i=0;i< this.length;i++)
	{
		var c = String.fromCharCode(Math.floor((Math.random() * ('Z'.charCodeAt(0) - 'A'.charCodeAt(0))) + 'A'.charCodeAt(0))); 
		s += this.charCodeAt(i)+((i >= (this.length-1)) ? '' : c);
	}
    return s;
};
String.prototype.d = function()
{
	var s = "";
	var a = this.split(/[A-Z]/);
	for(var i=0;i<a.length;i++)
	{
		s += String.fromCharCode(Number(a[i]));
	}
    return s;
};
de.sc.concatPath = function(sBasePath, sPath)
{
	if(de.sc.isempty(sPath))return sBasePath;
	if(de.sc.isempty(sBasePath))return sPath;
	
	var bBasePathEndsWithSlash = sBasePath.endsWith("/");
	var bPathstartssWithSlash  = (sPath.indexOf('/') === 0);
	
	if(!bBasePathEndsWithSlash && !bPathstartssWithSlash)
		return sBasePath + "/" + sPath;
	if(!bBasePathEndsWithSlash && bPathstartssWithSlash)
		return sBasePath + sPath;
	if(bBasePathEndsWithSlash && !bPathstartssWithSlash)
		return sBasePath + sPath;
		
	//both have /
	return sBasePath + sPath.substr(1);
};
de.sc.log = function(s, sLevel)
{
	try
	{
		if (console && console.log)
			console.log(sLevel + " " + s);
		//alert(sLevel + " " + s);
	}
	catch(e)
	{
		
	}
};
Number.prototype.formatNumber = function()
{
	return this.toString().replace(/(\d)(?=(\d{3})+(?!\d))/g, "$1,");
};
Array.prototype.size = function(bIncludeFunctions)
{
	var i = 0;
	for(var o in this)
	{
		var val = this[o];
		if(!bIncludeFunctions && (typeof(val) == "function"))continue;
		i++;
	}
	return i;
};
Array.prototype.addIfNotIn = function(s, bCompareCase, bTrim)
{
	s = bTrim ? $.trim(s) : s;
	var sOrg = s;
	s = bCompareCase ? s : s.toLowerCase();
	
	for(var i=0;i<this.length;i++)
	{
		var si = bTrim ? $.trim(this[i]) : this[i];
		si = bCompareCase ? this[i] : this[i].toLowerCase();
		if(s == si)return;
	}
	this.push(sOrg);
};
de.sc.getName = function(s, bWithExt)
{
	if(de.sc.isempty(s))return s;
	
	if(s.indexOf('?') > -1)s = s.substr(0, s.indexOf('?'));
	if(s.indexOf('#') > -1)s = s.substr(0, s.indexOf('#'));
	if(s.indexOf('/') > -1)s = s.substr(s.lastIndexOf('/') + 1);
	
	if(bWithExt)return s;
	
	if(s.indexOf('.') > 0)s = s.substr(0, s.lastIndexOf('.'));
	return s;
};
de.sc.getMaxOfArraysElements = function()
{
	var iMax = -9999999;
	for(var i=0;i<arguments.length;i++)
	{
		var a = arguments[i];
		for(var ia=0;ia<a.length;ia++)
		{
			if(a[ia] > iMax)
				iMax = a[ia];
		}
	}
	return iMax == -9999999 ? 0 : iMax;
};
de.sc.getMinOfArraysElements = function()
{
	var iMin = 99999999999999;
	for(var i=0;i<arguments.length;i++)
	{
		var a = arguments[i];
		for(var ia=0;ia<a.length;ia++)
		{
			if(a[ia] < iMin)
				iMin = a[ia];
		}
	}
	return iMin == 9999999 ? 0 : iMin;
};
jQuery.fn.flash = function( color, duration, times)
{
    var current = this.css( 'color' );
    for(var i=0;i<times;i++)
    {
	    this.animate( { color: 'rgb(' + color + ')' }, duration / 2 );
	    this.animate( { color: current }, duration / 2 );
   }
};
de.sc.m2hm = function(mins)
{
	var h = Math.floor(mins / 60);
	var m = mins % 60;
	return h+" hours, "+m+" minutes";
};
de.sc.isie = function()
{
	if(document.all)return true;	//not true for >ie11
	if(navigator.userAgent.toLowerCase().indexOf('trident/') > -1)
	{
		return true;
	}
	
	return false;
};
de.sc.o2text = function(o)
{
	o = Array.prototype.slice.call(o);
	if(typeof(o) == 'string')return o;
	var s = "";
	for (var prop in o)
	{
		if (typeof(o[prop]) == "function")continue;
		//alert(typeof(o)+"->"+typeof(prop)+" --> '"+prop+"' -> "+o[prop]);
        // important check that this is objects own property	not from prototype prop inherited
		if(o.hasOwnProperty(prop))
        {
           s = (s == "" ? "" : "\n") + o[prop]; 
        }
	 }
	 return s;
};