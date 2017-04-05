de.sc.portal.env = {};

de.sc.portal.env.WAR_SSS			= "com.unify.sales.service.webapp.war";
de.sc.portal.env.WAR_SSS_PRICING	= "com.unify.sales.service.pricing.webapp.war";
de.sc.portal.env.WAR_SSS_EISIMAT	= "com.unify.sales.service.eis.imaterial.proxy.webapp.war";
de.sc.portal.env.WAR_SE				= "?.war";
de.sc.portal.env.WAR_ESB			= "com.unify.sales.esb.logging.webapp.war";
de.sc.portal.env.WAR_ESBUI			= "com.unify.sales.esb.ui.war";
de.sc.portal.env.WAR_PORTS			= "ports";
de.sc.portal.env.WAR_SMO			= "smartOffer.war";
de.sc.portal.env.WAR_ESBUIPORTAL	= "esbuiportal";
de.sc.portal.env.WAR_SSS_MONGOMIGR	= "com.unify.sales.service.pricing.primamigration.webapp.war";
de.sc.portal.env.WAR_SE_MONGOMIGR	= "com.unify.service.engine.migration.webapp.war";

de.sc.portal.env.SERVICE_BUILD		= "build";
de.sc.portal.env.SERVICE_VALIDATION = "validation";
de.sc.portal.env.SERVICE_PRICING    = "pricing";
de.sc.portal.env.SERVICE_EISIMAT    = "imaterial";
de.sc.portal.env.SERVICE_SMO		= "smartOffer";
de.sc.portal.env.SERVICE_ESBUIPORTAL= "esbuiportal";
de.sc.portal.env.SERVICE_PORT		= "port";
de.sc.portal.env.SERVICE_ESB		= "com.unify.sales.esb.logging.webapp";
de.sc.portal.env.SERVICE_ESBUI		= "esbui";
de.sc.portal.env.SERVICE_SSS_MONGOMIGR = "com.unify.sales.service.pricing.primamigration.webapp";
de.sc.portal.env.SERVICE_SE_MONGOMIGR  = "com.unify.service.engine.migration.webapp";

de.sc.portal.env.DBSERVER_MYSQL 	= "MySQL";
de.sc.portal.env.DBSERVER_ORACLE 	= "Oracle";
de.sc.portal.env.DBSERVER_MONGO 	= "Mongo";

de.sc.portal.env.getProdPort = function()  
{
	var url = (de.sc.isempty(""+window.location.port) || (""+window.location.port == "80")) ? "/prod/sss/port/" : "/cgi-bin/get.cgi?"+escape("http://mchp486a.global-intra.net/prod/sss/port/");
	
	var prodPort = de.sc.geturlcontent(url);
	if (prodPort === null)
	{
		if(window.location.href.indexOf("http") === 0)
		{
			de.sc.log("env.port: !port:"+prodPort, de.sc.ERR);
		}
		prodPort = 8080;	//local
	}
	return +prodPort;
};
de.sc.portal.env.maketables = function()  
{
	var prodPort = de.sc.portal.env.getProdPort();

	var clusters = new Array();
	var servers = new Array();
	clusters.push(8080);
	clusters.push(9080);
	
	for(var iclusters=0;iclusters < clusters.length; iclusters++)
	{
		var cluster = new Array();
		var bProd = clusters[iclusters] == prodPort;
		
		var apache = new de.sc.portal.env.apacheServer(486, clusters[iclusters], 10, bProd, "172.30.66.151");
		cluster.push(apache);
		cluster.push(new de.sc.portal.env.server(487, clusters[iclusters] == 9080 ? 9090 : clusters[iclusters], 32, bProd, "172.30.66.153", apache));
		cluster.push(new de.sc.portal.env.server(488, clusters[iclusters] == 9080 ? 9090 : clusters[iclusters], 32, bProd, "172.30.66.154", apache));
		cluster.push(new de.sc.portal.env.server(490, clusters[iclusters], 32, bProd, "172.30.66.152", apache));
		cluster.push(new de.sc.portal.env.server(491, clusters[iclusters], 32, bProd, "172.30.66.156", apache));
		cluster.push(new de.sc.portal.env.server(493, clusters[iclusters], 32, bProd, "172.30.66.158", apache));
		cluster.push(new de.sc.portal.env.server(494, clusters[iclusters], 32, bProd, "172.30.66.159", apache));
		cluster.push(new de.sc.portal.env.server(495, clusters[iclusters], 32, bProd, "172.30.66.160", apache));
		
		var s = "";
		for(var icluster=0;icluster<cluster.length; icluster++)
		{
			var server	= cluster[icluster];
			s += de.sc.portal.env.getDIV(server, 0);
		}	//end for(var icluster=0;icluster<cluster.length; icluster++)
		
		$("#cluster"+clusters[iclusters]).html(s);
		if(bProd)
		{
			$("#cluster"+clusters[iclusters]+"prodmarker").html(" PROD ");
		}
		
		servers.push(cluster);
		
	}	//end for(var iclusters=0;iclusters < clusters.length; iclusters++)
	
	de.sc.portal.env.schedule();
	
	var __i = 1;
	$(document).on( "click", ".onexpand", function(event)	//LIVE, for all trees!
	//$(".onexpand").click(function(event)
	{
		event.stopPropagation();
		event.preventDefault();
		$(this).children("img").toggle();
		
		//$(this).parent().children("div").toggle("explode", { pieces:9 }, "slow");		//if(bouncingNotAcceptable)(activate these 2 lines)
		//return;
		
		__i++;
		if((__i % 4) === 0)
			$(this).parent().children("div").toggle("explode", { pieces:9 }, "slow");		//ok
		else if((__i % 3) === 0)
			$(this).parent().children("div").toggle("drop", { direction:"left" }, "slow" );	//!ok
		else if((__i % 2) === 0)
			$(this).parent().children("div").toggle("bounce", { times: 3 }, "slow" );		//!ok
		else
			$(this).parent().children("div").toggle("slow");								//!ok
	});
	
	$(".nagios").hover(
		function(ev)
		{
	        var mouseX = ev.pageX;
	        var mouseY = ev.pageY;
	        var cssObj =
	        {
              'position' : 'absolute',
              'left' : mouseX + 5 + 'px',
              'top' : mouseY + 5 + 'px'
	        };
	        $('#nagiosimg').attr('src', $(ev.target).attr('src')).css(cssObj).show("slow");
		},
		function(ev)
		{
			$('#nagiosimg').hide("slow");
		});

	return servers;
};
de.sc.portal.env.getDIV = function(o, iLevel)
{
	if(iLevel > 9)
	{
		return "ERR getDIV 1 ("+iLevel+")";
	}
	var children = o.getChildren();
	var s = " <div class='env envlevel"+iLevel+"' "+(iLevel > 0 ? "style='display:none;'" : "")+"> ";		//TODO: bgcolor, if(iLevel)hidden

	if(children !== null)
	{	
		s += " <a href='#' class='awithplusminus onexpand'><img src='./img/plus.gif' /><img src='./img/minus.gif' style='display:none;' /></a> ";
	}
	else
	{
		s += " <img src='./img/spacer.gif' style='width:9px;' /> ";
	}
	{
		var url  = o.getUrl();
		var name = o.getName();
		if(url !== null)
		{
			s += " <a href='"+url+"' target='_blank' class='awithplusminus'>" + name+ "</a> ";
		}
		else
		{
			s += name;
		}
		{
			try
			{
				s += o.getExtra();
			}
			catch(e)
			{
				//normal case
			}
		}
	}
	if(children !== null)
	{	
		for(var i=0;i<children.length;i++)
		{
			s += de.sc.portal.env.getDIV(children[i], iLevel+1);
		}
	}

	s += " </div> ";
	return s;
};
de.sc.portal.env.server = (function()
{
	function server(iMachineIndex, iPort, iRAM, bProd, sIP, apache)
	{
		this.iMachineIndex = iMachineIndex;
		this.iPort = iPort;
		this.iRAM = iRAM;
		this.bProd = bProd;
		this.sIP = sIP;
		this.apache = apache;
	};	
	server.prototype.getUrl = function()
	{
		return "http://mchp"+this.iMachineIndex+"a.global-intra.net:"+this.iPort+"/";
	};
	server.prototype.getName = function()
	{
		return this.getUrl();
	};
	server.prototype.getSessionsPlaceHolderId = function()
	{
		var id = this.sIP + ":" + this.iPort;
		id = "id"+id.replace(/\./g, "_").replace(/:/g, "_");
		return id;
	};
	server.prototype.getExtra = function()
	{
		return	"<a href='https://monitoring.global-intra.net/nagios/cgi-bin/status.cgi?host=MMO_JBoss_Prod_mchp"+this.iMachineIndex+"a' target='_new'><img src='./img/nagios.png' class='ico nagios' title='NAGIOS' /></a> " + 
				" <span id='"+this.getSessionsPlaceHolderId()+"' class='numsessions'></span>";
	};
	server.prototype.getChildren = function()
	{
		var wars = new Array();
		
		if((this.iMachineIndex == 487) || (this.iMachineIndex == 488))
		{
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SMO));
		}
		else if(this.iMachineIndex == 490)
		{
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_ESB));
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_ESBUI));
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS_MONGOMIGR));
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SE_MONGOMIGR));
		}
		else if((this.iMachineIndex == 491) || (this.iMachineIndex == 493) || (this.iMachineIndex == 494) || (this.iMachineIndex == 495))
		{
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS));
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS_PRICING));
			wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS_EISIMAT));
		}
		else
		{
			de.sc.log("env.srv: !MachineIndex:"+this.iMachineIndex, de.sc.ERR);
		}
		
		return wars;
	};
	
	return server;

})();
de.sc.portal.env.apacheServer = (function(_super)
{
	 __extends(apacheServer, _super);											//inherit
	
	function apacheServer(iMachineIndex, iPort, iRAM, bProd, sIP)
  	{
  		apacheServer.__super__.constructor.apply(this, arguments);				//call super constr
  		
		if(iPort == 8080)		this.iPort = 80;
		else if(iPort == 9080)	this.iPort = 8080;
		else de.sc.log("apacheServer: !port:"+iPort, de.sc.ERR);
	};
	apacheServer.prototype.getModClusterManagerURL = function()
	{
		var url = "http://mchp"+this.iMachineIndex+"a.global-intra.net:"+(this.iPort == 80 ? "10001":"20001")+"/mod_cluster_manager";
		return url;
	};
	apacheServer.prototype.getExtra = function()
	{
		var url = this.getModClusterManagerURL();
		//var sbase = apacheServer.__super__.getExtra.call(this);				//call base	//call super
		var sNagios = (this.iPort == 80 ? "&nbsp;&nbsp;&nbsp;":"") + "<a href='https://monitoring.global-intra.net/nagios/cgi-bin/status.cgi?host=MMO_Web_Prod_mchp"+this.iMachineIndex+"a' target='_new'><img src='./img/nagios.png' class='ico nagios' title='NAGIOS' /></a>";
		return sNagios + "<a href='"+url+"' target='_new'><img src='./img/mod_cluster.png' class='ico nagios' title='MOD CLUSTER' /></a>";
	};
	apacheServer.prototype.getChildren = function()
	{
		var wars = new Array();

		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SMO));
		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_ESBUI));
		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_ESBUIPORTAL));
		if(this.iPort == 80)wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_PORTS));
		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS));
		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS_PRICING));
		wars.push(new de.sc.portal.env.war(this, de.sc.portal.env.WAR_SSS_EISIMAT));

		return wars;
	};
	
	return apacheServer;
	
})(de.sc.portal.env.server);
de.sc.portal.env.war = (function()
{
	function war(server, type)
	{
		this.server = server;
		this.type = type;
	};	
	war.prototype.getChildren = function()
	{
		var ss = new Array();
		if(this.type == de.sc.portal.env.WAR_SSS)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_BUILD));
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_VALIDATION));
		}
		else if(this.type == de.sc.portal.env.WAR_SSS_PRICING)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_PRICING));
		}
		else if(this.type == de.sc.portal.env.WAR_SSS_EISIMAT)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_EISIMAT));
		}
		else if(this.type == de.sc.portal.env.WAR_SMO)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_SMO));
		}
		else if(this.type == de.sc.portal.env.WAR_ESBUIPORTAL)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_ESBUIPORTAL));
		}
		else if(this.type == de.sc.portal.env.WAR_PORTS)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_PORT, "/prod/sss/port/"));
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_PORT, "/prod/se/port/" ));
		}
		else if(this.type == de.sc.portal.env.WAR_ESB)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_ESB));
		}
		else if(this.type == de.sc.portal.env.WAR_ESBUI)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_ESBUI));
		}
		else if(this.type == de.sc.portal.env.WAR_SSS_MONGOMIGR)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_SSS_MONGOMIGR));
		}
		else if(this.type == de.sc.portal.env.WAR_SE_MONGOMIGR)
		{
			ss.push(new de.sc.portal.env.service(this, de.sc.portal.env.SERVICE_SE_MONGOMIGR));
		}
		else
		{
			de.sc.log("env.war: !type:"+this.type, de.sc.ERR);
		}
		return ss;
	};
	war.prototype.getUrl = function()
	{
		return null;
	};
	war.prototype.getName = function()
	{
		return this.type;
	};
	
	return war;
	
})();
de.sc.portal.env.service = (function()
{
	function service(war, type, urlSuffix)
	{
		this.war = war;
		this.type = type;
		this.urlSuffix = urlSuffix;
		if(type === undefined)
		{
			de.sc.log("env.service: !type! war.type:"+this.war.type, de.sc.ERR);
		}
	};
	service.prototype.getUrl = function()
	{
		if(this.type == de.sc.portal.env.SERVICE_PORT)
		{
		   	return de.sc.concatPath(this.war.server.getUrl(), this.urlSuffix);
		}
		if((this.war.type == de.sc.portal.env.WAR_SSS_MONGOMIGR) ||
		   (this.war.type == de.sc.portal.env.WAR_SE_MONGOMIGR))
		{
		   	return null;
		}
		if(this.war.type == de.sc.portal.env.WAR_ESB)
		{
			//eg. http://mchp406a.global-intra.net:7070/com.unify.sales.esb.logging.webapp/.getLog
		   	return de.sc.concatPath(this.war.server.getUrl() + (de.sc.getName(this.war.getName(), false))) + "/.getLog?type=sss_someservice&id=someid";
		}
		if(this.war.type == de.sc.portal.env.WAR_ESBUI)
		{
		   	return de.sc.concatPath(this.war.server.getUrl() + (de.sc.getName(this.war.getName(), false))) + "/" + this.type;	//e.g. http://mchp486a.global-intra.net/com.unify.sales.esb.ui/esbui
		}
		if((this.war.type == de.sc.portal.env.WAR_SMO) ||
		   (this.war.type == de.sc.portal.env.WAR_ESBUIPORTAL))
		{
		   	return de.sc.concatPath(this.war.server.getUrl() + de.sc.getName(this.war.getName(), false)) + "/";
		}

		return de.sc.concatPath(this.war.server.getUrl() + (de.sc.getName(this.war.getName(), false))) + "/ws/" + this.type.upperFirst(false) + "Service/" + this.type.upperFirst(true) + "Service.wsdl";
	};
	service.prototype.getName = function()
	{
		if(this.type == de.sc.portal.env.SERVICE_PORT)
		{
		   	return this.urlSuffix;
		}
		
		var n = de.sc.getName(this.getUrl(), false);
		if(de.sc.isempty(n))
		{
			var u = this.getUrl();
			if (u === null) return de.sc.getName(this.war.getName(), false);
			u = u.substr(0, u.length - 1);
			return de.sc.getName(u, false);
		}
		return n;
	};
	service.prototype.getChildren = function()
	{
		if(this.type == de.sc.portal.env.SERVICE_VALIDATION)
			return null;
		if(this.type == de.sc.portal.env.SERVICE_EISIMAT)
			return null;
		if(this.type == de.sc.portal.env.SERVICE_ESBUIPORTAL)
			return null;
		if(this.type == de.sc.portal.env.SERVICE_PORT)
			return null;
			
		var dbservers = new Array();
		
		if((this.type == de.sc.portal.env.SERVICE_BUILD) ||
		   (this.type == de.sc.portal.env.SERVICE_SMO) ||
		   (this.type == de.sc.portal.env.SERVICE_ESB) ||
		   (this.type == de.sc.portal.env.SERVICE_ESBUI))
		{
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_MYSQL));
		}
		else if(this.type == de.sc.portal.env.SERVICE_SSS_MONGOMIGR)
		{
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_ORACLE));
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_MONGO));
		}
		else if(this.type == de.sc.portal.env.SERVICE_SE_MONGOMIGR)
		{
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_MONGO));
			//MySQL? ENScore? HSQL(local)?
		}
		else if(this.type == de.sc.portal.env.SERVICE_PRICING)
		{
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_MYSQL));
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_MONGO));
			dbservers.push(new de.sc.portal.env.dbserver(this, de.sc.portal.env.DBSERVER_ORACLE));
		}
		else
		{
			de.sc.log("env.srv: !type:"+this.type, de.sc.ERR);
		}
		return dbservers;
	};
	
	return service;
	
})();
de.sc.portal.env.dbserver = (function()
{
	function dbserver(service, type)
	{
		this.service = service;
		this.type = type;
	};	
	dbserver.prototype.getUrl = function()
	{
		if(this.type == de.sc.portal.env.DBSERVER_MONGO)
			return "http://"+this.getServerName()+".global-intra.net:28017/";
		return null;
	};
	dbserver.prototype.getName = function()
	{
		return this.getServerName() + " ("+this.type+")";
	};
	dbserver.prototype.getServerName = function()
	{
		if(this.type == de.sc.portal.env.DBSERVER_MYSQL)
			return "mchp421a";
		if(this.type == de.sc.portal.env.DBSERVER_ORACLE)
			return "mchp838a";
		if(this.type == de.sc.portal.env.DBSERVER_MONGO)
			return "mchp363a";
		de.sc.log("env.dbsrv: !type:"+this.type, de.sc.ERR);
		return "";
	};
	dbserver.prototype.getChildren = function()
	{
		var dbs = new Array();
		
		var dbpostfix = (this.service.war.server.bProd) ? "a" : "b";
		
		if(this.type == de.sc.portal.env.DBSERVER_MYSQL)
		{
			if((this.service.type == de.sc.portal.env.SERVICE_BUILD) ||
			   (this.service.type == de.sc.portal.env.SERVICE_PRICING) ||
			   (this.service.type == de.sc.portal.env.SERVICE_ESB) ||
			   (this.service.type == de.sc.portal.env.SERVICE_ESBUI))
			{
				dbs.push(new de.sc.portal.env.db(this, "dbntx-soa-sss-prod-"+dbpostfix, "soa-sss-prod-"+dbpostfix));
			}
			else if(this.service.type == de.sc.portal.env.SERVICE_SMO)
			{
				dbs.push(new de.sc.portal.env.db(this, "dbtx-soa-smo-prod-"+dbpostfix, "soa-smo-prod-"+dbpostfix));
			}
			else
			{
				de.sc.log("env.dbserver: (a) !type:"+this.type+"\nservtype:"+this.service.type, de.sc.ERR);
				return null;
			}
			//TODO: SE
			return dbs;
		}
		if(this.type == de.sc.portal.env.DBSERVER_MONGO)
		{
			if((this.service.type == de.sc.portal.env.SERVICE_PRICING) ||
			   (this.service.type == de.sc.portal.env.SERVICE_SSS_MONGOMIGR))
			{
			   	dbs.push(new de.sc.portal.env.db(this, "sss-migration-db1-"+dbpostfix	 , "sen-soa-sales-"+dbpostfix));
			   	dbs.push(new de.sc.portal.env.db(this, "sss-migration-db2-"+dbpostfix	 , "sen-soa-sales-"+dbpostfix));
			   	dbs.push(new de.sc.portal.env.db(this, "sss-migration-admin-db-"+dbpostfix, "sen-soa-sales-"+dbpostfix));
			}
			else if(this.service.type == de.sc.portal.env.SERVICE_SE_MONGOMIGR)
			{
			   	dbs.push(new de.sc.portal.env.db(this, "se-prod-db1-"+dbpostfix, "sen-soa-service-engine-"+dbpostfix));
			   	dbs.push(new de.sc.portal.env.db(this, "se-prod-db2-"+dbpostfix, "sen-soa-service-engine-"+dbpostfix));
			   	dbs.push(new de.sc.portal.env.db(this, "se-prod-db3-"+dbpostfix, "sen-soa-service-engine-"+dbpostfix));
			}
			else
			{
				de.sc.log("env.dbserver: (b) !type:"+this.type, de.sc.ERR);
				return null;
			}
			//TODO: SE
			return dbs;
		}
		if(this.type == de.sc.portal.env.DBSERVER_ORACLE)
		{
			if((this.service.type == de.sc.portal.env.SERVICE_PRICING) ||
			   (this.service.type == de.sc.portal.env.SERVICE_SSS_MONGOMIGR))
			{
			   	dbs.push(new de.sc.portal.env.db(this, "mchp838a.global-intra.net", "pmdprod"));
			}
			else
			{
				de.sc.log("env.dbserver: !type:"+this.type, de.sc.ERR);
				return null;
			}
			return dbs;
		}
	};
	
	return dbserver;

})();
de.sc.portal.env.db = (function()
{
	function db(dbserver, dbName, userName)
	{ 
		this.dbserver = dbserver;
		this.dbName = dbName;
		this.userName = userName;
	};	
	db.prototype.getName = function()
	{
		return this.dbName+" ("+this.userName+")";
	};
	db.prototype.getUrl = function()
	{
		if(this.dbserver.type == de.sc.portal.env.DBSERVER_MYSQL)
			return "http://"+this.dbserver.getServerName()+".global-intra.net:3306/"+this.dbName;
		return null;
	};
	db.prototype.getChildren = function()
	{
		return null;
	};
	
	return db;
	
})();

de.sc.portal.env.schedule = function()
{
	$(document).on(de.sc.portal.env.msg.MOD_CLUSTER_MANAGER, function(msg_data)
	{
		for(var iClusters=0;iClusters<msg_data["clusters"].length;iClusters++)
		{
			var cluster = msg_data["clusters"][iClusters]["cluster"];
			var srvr = null;
			
			for(var iCluster=0;iCluster<cluster.length;iCluster++)
			{
				srvr = cluster[iCluster];
				$("#"+srvr.getSessionsPlaceHolderId()).html(" ");
			}
			
			var data = msg_data["clusters"][iClusters]["content"];
			data = data.replace(/&/g, "");
			data = data.replace(/<!.*?>/g, "");
			
			var html = new de.sc.xml(data);
			var body = html.getXmlChild(html.XML, "body");
			
			var currentNode = null;
			
			if(!body || !body.childNodes)continue;
			
			for(var i=0;i<body.childNodes.length;i++)
			{
				var sub = body.childNodes[i];
				if((sub.nodeType == de.sc.XMLELEMENT_NODE) && (sub.nodeName.toLowerCase() == "h1"))
				{
					currentNode = null;
					var h1Text = $.trim(sub.childNodes[0].nodeValue);
					for(iCluster=0;iCluster<cluster.length;iCluster++)
					{
						srvr = cluster[iCluster];
						var srvrid = srvr.sIP+":"+srvr.iPort;
						if((h1Text.toLowerCase().indexOf("node ") === 0) && (h1Text.indexOf("http://"+srvrid) > 2))
						{
							currentNode = srvr;
							break;
						}
					}
					continue;
				}

				if((currentNode !== null) && !de.sc.isempty(sub.nodeValue) && (sub.nodeType == de.sc.XMLTEXT_NODE))
				{
					var nodeValue = sub.nodeValue.replace(/:/g, "_");
					var regex = /Num sessions_\s*(\d+)/;
					if (regex.test(nodeValue))
					{
						var nr = Number(nodeValue.match(regex)[1]);
						if (nr > 0)
						{
							$("#"+currentNode.getSessionsPlaceHolderId()).html("Active Sessions: "+nr);
						}
					}
				}
			}
		}	//end for(var i=0;i<data["clusters"].length;i++)
	});
};
