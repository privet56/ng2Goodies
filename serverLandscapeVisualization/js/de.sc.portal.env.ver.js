de.sc.portal.env.ver = {};

de.sc.portal.env.ver.tbl = null;

de.sc.portal.env.ver.onSelectTreeItem = function(event, data)
{
	angular.element(data.tree.$div).scope().$apply('treesHaveSelectedItems()');
};
de.sc.portal.env.ver.onGetSSSRuleVersions = function()
{
	$("#wait").show();
	$("#wait_msg").text(" ");
	
	de.sc.portal.env.ver.tbl.search('');
	de.sc.portal.env.ver.tbl.clear().draw();
	var services2call = new Array();

	for(var services=0; services < $("#service-tree").fancytree("getTree").getSelectedNodes().size(); services++)
	{
		if($("#service-tree").fancytree("getTree").getSelectedNodes()[services].hasChildren())
		{
			continue;
		}
		
		for(var envs=0; envs < $("#env-tree").fancytree("getTree").getSelectedNodes().size(); envs++)
		{
			if($("#env-tree").fancytree("getTree").getSelectedNodes()[envs].hasChildren())
			{
				continue;
			}
			var productType	= $("#service-tree").fancytree("getTree").getSelectedNodes()[services];
			var server		= $("#env-tree"    ).fancytree("getTree").getSelectedNodes()[envs];
			var service		= productType.parent;
			services2call.push(new de.sc.portal.env.ver.service2call(service.title, productType.title, server.title));
		}
	}
	for(var i = 0;i < services2call.length; i++)
	{
		services2call[i].setCheckLen(services2call.length);
		services2call[i].call();
	}
	/*
	$("#log").val("");
	for(var i = 0;i < services2call.length; i++)
	{
		alert("services2call.getServiceUrl():"+services2call[i].getServiceUrl());
		$("#log").val($("#log").val()+services2call[i].getServiceUrl()+"\n");
	}
	$("#log").val(("#log").val()+"after\n");
	*/
};
de.sc.portal.env.ver.service2call = (function()
{
	function service2call(service, productType, server)
	{
		this.service = service;
		this.productType = productType;
		this.server = server;
	};
	service2call.prototype.setCheckLen = function(iChecksCount)
	{
		this.iChecksCount = iChecksCount;
	};	
	service2call.prototype.getServiceUrl = function()
	{
		return "http://"+this.server.split(":")[0]+".global-intra.net:"+this.server.split(":")[1]+"/com.unify.sales.service.webapp/ws/"+this.service.toLowerCase()+"Service/"+this.service.upperFirst(true)+"Service.wsdl";
	};
	service2call.prototype.getSOAPCallXMLUrl = function()
	{
		return "./soap/"+this.service.upperFirst(true)+"_"+this.productType.toUpperCase()+"_VersionCheck.xml";
	};
	service2call.prototype.post = function(xmldata2post)
	{
		var s2c   = this;
		var local = (window.location.href.indexOf("http://localhost") == 0); 
		var url   = local ? (s2c.getSOAPCallXMLUrl()+"_response") : ("/cgi-bin/post.cgi?"+escape(s2c.getServiceUrl()));
		
		xmldata2post = xmldata2post.replace(/(\r\n|\n|\r\t)/gm,"");
		
		$.ajax
		({
			type: local ? "GET" : "POST",
			data: xmldata2post,
			url: url,
			dataType:"text"	
		})
		.success(function(data)
		{
			s2c.fillresulttablerecord(data, false);
		})
		.error(function(xhr, statusmsg, err)
		{
			de.sc.log("\ns2c:call:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\n'"+url+"'", de.sc.WRN);
			s2c.fillresulttablerecord(statusmsg+"\n"+err, true);
		});
	};
	service2call.prototype.call = function()
	{
		var s2c = this;
		$.ajax
		({
			url: s2c.getSOAPCallXMLUrl(), dataType:"text"
		})
		.success(function(data)
		{
			s2c.post(data);
		})
		.error(function(xhr, statusmsg, err)
		{
			de.sc.log("\ns2c:call:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\n'"+url+"'", de.sc.WRN);
			s2c.fillresulttablerecord(statusmsg+"\n"+err, true);
		});
	};
	service2call.prototype.getVersion = function(data)
	{
		try
		{
			var soapresponse = new de.sc.xml(data);
			var body = soapresponse.getXmlChild(soapresponse.XML,"body");
			if(!body)
			{
				var s = "Error retriving the "+this.service+" Service version (no body found)";
				de.sc.log("\ns2c:getVersion:\nE:0:"+s+"\n"+data, de.sc.WRN);
				return s;
			}
			var resp = soapresponse.getXmlChild(body,null);
			var trns = soapresponse.getXmlChild(resp,null);
			var site = soapresponse.getXmlChild(trns,null);
			if(!site)
			{
				var s = "Error retriving the "+this.service+" Service version (no site found)";
				de.sc.log("\ns2c:getVersion:\nE:6:"+s, de.sc.WRN);
				return s;
			}
			if(this.service.toLowerCase() == "build")
			{
				for(var i=0;i<site.childNodes.length;i++)
				{
					var sub = site.childNodes[i];
					if (sub.nodeType != de.sc.XMLELEMENT_NODE)
						continue;
					var attr = soapresponse.getXmlAttr(sub, "BB_DisplayCat");
					var attr_qty = soapresponse.getXmlAttr(sub, "Qty");
					if((attr_qty != null) && (attr != null) && (attr.toLowerCase() == "hidden"))
					{
						var desc = soapresponse.getXmlChild(sub, null);
						var text = soapresponse.getXmlChild(desc,null);
						return "<span style='color:blue;'>Rule-Version: "+attr_qty+"; </span> \n "+soapresponse.getXmlAttr(text, "Short_Desc_Int").replace(">","").replace("<","");
					}
				}
				de.sc.log("\ns2c:getVersion:\nE:2:"+site, de.sc.WRN);
				return "Error retriving the "+this.service+" Service version (c)";
			}
			else if(this.service.toLowerCase() == "validation")
			{
				var usec = soapresponse.getXmlChild(site,null);
				for(var i=0;i<usec.childNodes.length;i++)
				{
					var feat = usec.childNodes[i];
					if (feat.nodeType != de.sc.XMLELEMENT_NODE)
						continue;
					var feat_id = soapresponse.getXmlAttr(feat, "Id");
					//if((feat_id != null) && (feat_id.toLowerCase().indexOf("subscriber_") > -1))
					{
						for(var i=0;i<feat.childNodes.length;i++)
						{
							var serviceReport = feat.childNodes[i];
							if (serviceReport.nodeType != de.sc.XMLELEMENT_NODE)
								continue;
							var attr_type = soapresponse.getXmlAttr(serviceReport, "Type");
							if((attr_type != null) && (attr_type.toLowerCase() == "info"))
							{
								var desc = soapresponse.getXmlChild(serviceReport, null);
								if (desc == null) continue;
								var text = soapresponse.getXmlChild(desc,null);
								if (text == null) continue;
								var attr_desc = soapresponse.getXmlAttr(text, "Desc");
								if (attr_desc == null) continue;
								if (attr_desc.indexOf(" = v") > 0)
									return attr_desc.replace(">","").replace("<","");
							}
						}
						de.sc.log("\ns2c:getVersion:\nE:3:"+site, de.sc.WRN);
					}
				}
				de.sc.log("\ns2c:getVersion:\nE:4:"+site, de.sc.WRN);
				return "Error retriving the "+this.service+" Service version (b)";
			}
			else
			{
				de.sc.log("\ns2c:getVersion:\nunknown service:"+this.service.toLowerCase(), de.sc.WRN);
				return "Error retriving the "+this.service+" Service version (a)";
			}
		}
		catch(e)
		{
			de.sc.log("\ns2c:getVersion:\nE:1:"+e, de.sc.WRN);
			return "Error retriving the "+this.service+" Service version\n"+e;
		}
	};
	service2call.prototype.fillresulttablerecord = function(data, isError)
	{
		//#,OK?,Server,URL,productType,versionMessage
		
		var entries_now = de.sc.portal.env.ver.tbl.data().length;
		var bok 		= !isError;
		var href 		= this.getServiceUrl();
		var version 	= bok ? this.getVersion(data) : data;
		if(!version || ($.trim(version.toLowerCase()).indexOf("error") == 0))
		{
			bok = false;
			isError = true;
		}
		//version = version.replace(">","").replace("<","");
		
		de.sc.portal.env.ver.tbl.row.add([
		 			""+(entries_now + 1),
		 			((bok === true) ? '&nbsp;' : '!') + "OK <img src='"+((bok === true) ? './img/check_ok.png' : './img/check_notok.png')+"' data-ok='"+bok+"' />",
		 			this.server,
		 			"<a href='"+href+"' target='_new' class='"+((bok === true) ? 'check_ok' : "check_notok\' style='color:red;")+"'>"+de.sc.getName(href)+"</a>",
		 			this.productType,
		 			version
		         ]).draw();
		
		$("#wait_msg").text(" "+(entries_now + 1)+"/"+this.iChecksCount+" ");
		
		if(this.iChecksCount <= (entries_now + 1))
		{
			$("#wait").hide("drop", { direction:"right" }, 2222 );
		}
	};
	
	return service2call;

})();
