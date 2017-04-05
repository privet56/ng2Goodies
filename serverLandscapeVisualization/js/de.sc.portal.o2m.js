de.sc.portal.o2m = {};

de.sc.portal.o2m.machinewidth = 150;
de.sc.portal.o2m.machineheight= 50;
de.sc.portal.o2m.paperwidth = 1000;
de.sc.portal.o2m.paperheight= document.all ? 500 : 550;

de.sc.portal.o2m.tooltips=new Array();
de.sc.portal.o2m.allSets=null;
de.sc.portal.o2m.curGlow=null;

angular.module("app", ["lib"]).controller("ctrl", ['$scope', '$rootScope', '$http', '$interval', '$timeout', '$interval', '$log', function ($scope, $rootScope, $http, $interval, $timeout, $interval, $log)
{
	$scope.title = "Oracle2Mongo Copy Jobs";
	
	$scope.data = { };	//init
	
	$scope.$on('$includeContentLoaded', function()
	{
		de.sc.portal.nav.onReady($log, $scope.title);
	});

	$scope.showmsg = function(msg, isError)
	{
		if (isError && (msg.length < 11))
			msg = "An error occured (" + msg + ")";
		
		$rootScope.$broadcast(de.sc.a.showmessage, {msg:msg, isError:isError});
	};
}]);

var __recDepth = 0;
de.sc.portal.o2m.getDetails = function()
{
	var a = Array.prototype.slice.call(arguments);
	var s = "";
	//for(var i=0;i<a.length;i++)
	for (var i in a)
	{
		if(a == a[i])continue;
		if(a[i])
		{
			//alert("__recDepth:"+__recDepth+"\na.len:"+a.length+"\ni:"+i+"\na[i]:"+a[i]+"\ntype:"+typeof(a[i])+"\narguments[i].length:"+a[i].length+"\niasText:>"+de.sc.o2text(a[i])+"<\ns:"+s+"\nargsText:"+de.sc.o2text(a));
		}
		else
		{
			//alert("__recDepth:"+__recDepth+"\na.len:"+a.length+"\ni:"+i+"\nUNDEFINED\nargsText:"+de.sc.o2text(a));
			continue;
		}

		if(typeof(a[i]) == "string")
		{
			if(jQuery.trim(a[i]).length > 0)
			{
				s += (s == "" ? "" : "\n") + jQuery.trim(a[i]);
			}
		}
		else if(a[i].length)
		{
			if(__recDepth < 4)
			{
				__recDepth++;
				var ss = jQuery.trim(de.sc.portal.o2m.getDetails.apply(this, Array.prototype.slice.call(a[i])));
				if (ss.length > 0)
				{
					s += (s == "" ? "" : "\n") + "\n" + ss;
				}
				__recDepth--;
			}
		}
	}
	{
		var a = s.split("\n");
		var aclean = new Array();
		for(i=0;i<a.length;i++)
		{
			aclean.addIfNotIn(a[i], false, true);
		}
		return aclean.join("\n");
	}
};
de.sc.portal.o2m.formatDetails = function(s)
{
	var re = "";
	var rehrefs = "";
	var a = s.split("\n");
	for(var i=0;i<a.length;i++)
	{
		s = jQuery.trim(a[i]);
		if(de.sc.isempty(s))continue;
		if(((s.indexOf("http://") == 0) || (s.indexOf("https://") == 0)) && (s.indexOf(" ") < 0))
		{
			rehrefs += "<div class='selecteditemdetailsentry'><a href='"+s+"' target='_blank'>"+s+"</a></div>";
		}
		else
		{
			re += "<div class='selecteditemdetailsentry'>"+s.upperFirst(true)+"</div>";
		}
	}
	
	return re + "<div class='selecteditemdetailsentry'>&nbsp;</div>" + rehrefs+"<br />";
};
de.sc.portal.o2m.desc = function(paper, o, text, lnk, args)
{
	var a = Array.prototype.slice.call(arguments);
	o.mouseover(function(e)
	{
		for(var i=0;i<de.sc.portal.o2m.tooltips.length;i++)
		{
			de.sc.portal.o2m.tooltips[i].attr("text", text.upperFirst(true));
			var rect = o.getBBox({isWithoutTransform:true});
			{
				if(document.all)
				{
					de.sc.portal.o2m.tooltips[i].attr({
						x: rect.x + 50,
						y: rect.y - 20
					}).toFront();
				}
				else
				{
					de.sc.portal.o2m.tooltips[i].attr({
						x: rect.x + 50,
						y: rect.y - 20
					}).transform(o.transform()).toFront();
				}
			}
		}
	})
	.mouseout(function(e)
	{
		for(var i=0;i<de.sc.portal.o2m.tooltips.length;i++)
		{
			de.sc.portal.o2m.tooltips[i].attr("text", '');
			de.sc.portal.o2m.tooltips[i].attr({
				x: -999,
				y: -999
				});
		}
	})
	.click(function(e)
	{
		de.sc.portal.o2m.allSets.attr('stroke-width', 0);
		if(!document.all)
		{
			if (de.sc.portal.o2m.curGlow != null)
				de.sc.portal.o2m.curGlow.remove();
			de.sc.portal.o2m.curGlow = o.glow({ color: "red", width: 5 });
		}
		else
		{
			o.attr({'stroke-width': 3, stroke:"red"});
		}
		__recDepth = 0;
		var s = de.sc.portal.o2m.getDetails.apply(this, a);
		var html = de.sc.portal.o2m.formatDetails(s);
		jQuery('#selecteditemdetails').html(html);
	});
};
de.sc.portal.o2m.makeMachineOracle = function(paper, level, machineIndex, machineCountOfLevel, text, osImage, detailsF)
{
	var rect = this.getBBox({isWithoutTransform:true});
	var width  = 32;
	var height = 32;
	var x = rect.x + ((rect.width / 2) - (width/2));
	var y = rect.y + (de.sc.portal.o2m.machineheight - height);
	var pic = paper.image("./img/oracle.png", x, y, width, height);
	de.sc.portal.o2m.desc(paper, pic, "Oracle Database", Array.prototype.slice.call(arguments));
};
de.sc.portal.o2m.makeMachineO2M = function(paper, level, machineIndex, machineCountOfLevel, text, osImage, detailsF)
{
	var rect = this.getBBox({isWithoutTransform:true});
	var width  = 32;
	var height = 32;
	var x = rect.x + ((rect.width / 2) - (width/2));
	var y = rect.y + (de.sc.portal.o2m.machineheight - height);
	var pic = paper.image("./img/jboss.png", x, y, width, height);
	de.sc.portal.o2m.desc(paper, pic, "Web Application on a JBoss WebServer", Array.prototype.slice.call(arguments));
};
de.sc.portal.o2m.makeMachineMongo = function(paper, level, machineIndex, machineCountOfLevel, text, osImage, detailsF)
{
	var rect = this.getBBox({isWithoutTransform:true});
	var width  = 22;
	var height = 32;
	var x = rect.x + ((rect.width / 2) - (width/2));
	var y = rect.y + (de.sc.portal.o2m.machineheight - height);
	var pic = paper.image("./img/mongo2.png", x, y, width, height);
	de.sc.portal.o2m.desc(paper, pic, "Mongo Database", Array.prototype.slice.call(arguments));
};
de.sc.portal.o2m.makeMachinePS = function(paper, level, machineIndex, machineCountOfLevel, text, osImage, detailsF)
{
	var isSE = (text.toLowerCase().indexOf("serviceengine") == 0);
	var wars = 0;
	if(isSE)
		wars = ((machineIndex == 1) || (machineIndex == 2) || (machineIndex == 3) || (machineIndex == 6)) ? 1 : 4;
	else
		wars = ((machineIndex == 1) || (machineIndex == 2)) ? 1 : 4;

	var rect = this.getBBox({isWithoutTransform:true});
	var width  = 32;
	var height = 32;
	var y = rect.y + (de.sc.portal.o2m.machineheight - height);

	for(var i=0;i<wars;i++)
	{
		var x = rect.x + ((rect.width / (wars+1)) * (i+1)) - (width / 2);
		var pic = paper.image("./img/jboss.png", x, y, width, height);
		var port =  (wars < 2) ? "" : "("+(i+1)+")";
		de.sc.portal.o2m.desc(paper, pic, "Web Application on a JBoss WebServer " + port, Array.prototype.slice.call(arguments));
	}
};
de.sc.portal.o2m.start = function()
{
	de.sc.portal.o2m.startsss();
	de.sc.portal.o2m.startse();
};
de.sc.portal.o2m.startse = function()
{
	var paper = Raphael(document.getElementById("container-se"), de.sc.portal.o2m.paperwidth * 1.2, de.sc.portal.o2m.paperheight);
	paper.canvas.style.backgroundColor = "#FFFFF0";
	
	var tt = paper.text(-999, -999, '');
	tt.attr({'stroke-width': 0, fill: 'red', 'font-size': 12, 'font-weight':'bold' });
	de.sc.portal.o2m.tooltips.push(tt);

	var oracleSet1  = de.sc.portal.o2m.makeMachine(paper, 0/*level*/, 1/*machIndex*/, 2/*#machinesOfLevel*/, "ORACLE on mchp839a", "solaris", de.sc.portal.o2m.makeMachineOracle, "Schema for the ENScore / STM Data - TEST");
	var oracleSet2  = de.sc.portal.o2m.makeMachine(paper, 0/*level*/, 2/*machIndex*/, 2/*#machinesOfLevel*/, "ORACLE on mchp505a", "solaris", de.sc.portal.o2m.makeMachineOracle, "Schema for the ENScore / STM Data - PROD");
	
	var o2mdev1Set = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 1/*machIndex*/, 5/*#machinesOfLevel*/, "oracle2Mongo cronJob on mchp614a"    , "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp614a.global-intra.net:8080/", "ENScore/STM Data", "Migration Job Start: every day, 20:01 CET", "JBoss01 (runs ca. 4 hours)");
	var o2mtestSet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 2/*machIndex*/, 5/*#machinesOfLevel*/, "oracle2Mongo cronJob on mchp407a"    , "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp407a.global-intra.net:8080/", "ENScore/STM Data", "Migration Job Start: every day, 01:10 CET", "(runs ca. 4 hours)");
	var o2mcluASet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 3/*machIndex*/, 5/*#machinesOfLevel*/, "oracle2Mongo on mchp490a - CLUSTER-A", "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp490a.global-intra.net:8081/", "ENScore/STM Data", "Migration Job Start: every day, 01:10 CET", "(runs ca. 4 hours)");
	var o2mcluBSet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 4/*machIndex*/, 5/*#machinesOfLevel*/, "oracle2Mongo on mchp490a - CLUSTER-B", "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp490a.global-intra.net:9081/", "ENScore/STM Data", "Migration Job Start: every day, 03:10 CET", "(runs ca. 4 hours)");
	var o2mdev2Set = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 5/*machIndex*/, 5/*#machinesOfLevel*/, "oracle2Mongo cronJob on mchp614a"    , "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp614a.global-intra.net:8081/", "ENScore/STM Data", "Migration Job Start: every day, 05:01 CET", "JBoss02 (runs ca. 4 hours)");	

	var mDev1Set = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 1/*machIndex*/, 5/*#machinesOfLevel*/, "Mongo DEV1 DB on mchp627a"     , "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp627a.global-intra.net:28017/");
	var mTestSet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 2/*machIndex*/, 5/*#machinesOfLevel*/, "Mongo TEST DB on mchp407a"     , "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp407a.global-intra.net:28017/");
	var mCluASet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 3/*machIndex*/, 5/*#machinesOfLevel*/, "Mongo CLUSTER A DB on mchp363a", "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp363a.global-intra.net:27017/");
	var mCluBSet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 4/*machIndex*/, 5/*#machinesOfLevel*/, "Mongo CLUSTER B DB on mchp363a", "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp363a.global-intra.net:37017/");
	var mDev2Set = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 5/*machIndex*/, 5/*#machinesOfLevel*/, "Mongo DEV2 DB on mchp627a"     , "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp627a.global-intra.net:28017/");

	var psDev1 = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 1/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine on port 8082\non mchp614a", "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp614a.global-intra.net:8082/", "DEV1");
	var psTest = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 2/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine on port 5050\non mchp407a", "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp407a.global-intra.net:5050/", "TEST/PRE-STAGE");
	var psPRES = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 3/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine on port 6060\non mchp407a", "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp407a.global-intra.net:6060/", "TEST/PRE-STAGE");
	var psCLUA = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 4/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine CLUSTER A"				 , "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp486a.global-intra.net:80/" ,  "CLUSTER A - PROD / PROD RC");
	var psCLUB = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 5/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine CLUSTER B"				 , "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp486a.global-intra.net:8080/", "CLUSTER B - PROD / PROD RC");
	var psDev2 = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 6/*machIndex*/, 6/*#machinesOfLevel*/, "ServiceEngine on port 8083\non mchp614a", "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp614a.global-intra.net:8083/", "DEV2");
	
	graffle.setup(paper,
			{from:oracleSet1, to:o2mdev1Set, linecolor:"red", ani:false},
			{from:oracleSet1, to:o2mtestSet, linecolor:"red", ani:false},
			{from:oracleSet2, to:o2mcluASet, linecolor:"red", ani:false},
			{from:oracleSet2, to:o2mcluBSet, linecolor:"red", ani:false},
			{from:oracleSet2, to:o2mdev2Set, linecolor:"red", ani:false},
			
			{from:o2mdev1Set, to:mDev1Set, linecolor:"blue", ani:false},
			{from:o2mtestSet, to:mTestSet, linecolor:"blue", ani:false},
			{from:o2mcluASet, to:mCluASet, linecolor:"blue", ani:false},
			{from:o2mcluBSet, to:mCluBSet, linecolor:"blue", ani:false},
			{from:o2mdev2Set, to:mDev2Set, linecolor:"blue", ani:false},
			
			{from:mDev1Set, to:psDev1, linecolor:"red", ani:false},
			{from:mTestSet, to:psTest, linecolor:"red", ani:false},
			{from:mTestSet, to:psPRES, linecolor:"red", ani:false},
			{from:mCluASet, to:psCLUA, linecolor:"red", ani:false},
			{from:mCluBSet, to:psCLUB, linecolor:"red", ani:false},
			{from:mDev2Set, to:psDev2, linecolor:"red", ani:false}
		);
};
de.sc.portal.o2m.startsss = function()
{
	var paper = Raphael(document.getElementById("container-sss"), de.sc.portal.o2m.paperwidth, de.sc.portal.o2m.paperheight);
	paper.canvas.style.backgroundColor = "#FFFFF0";
	
	var tt = paper.text(-999, -999, '');
	tt.attr({'stroke-width': 0, fill: 'red', 'font-size': 12, 'font-weight':'bold' });
	de.sc.portal.o2m.tooltips.push(tt);

	var oracleSet  = de.sc.portal.o2m.makeMachine(paper, 0/*level*/, 1/*machIndex*/, 1/*#machinesOfLevel*/, "ORACLE on mchp612a", "solaris", de.sc.portal.o2m.makeMachineOracle, "Schema: 'SMART'", "'Seeing' PMD and PRIMA PROD Data");
	
	var o2mtestSet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 1/*machIndex*/, 3/*#machinesOfLevel*/, "oracle2Mongo cronJob on mchp406a"    , "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp406a.global-intra.net:8080/", "Migration Job Start: every day, 05:35 CET", "(runs ca. 5-6 hours)");
	var o2mcluASet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 2/*machIndex*/, 3/*#machinesOfLevel*/, "oracle2Mongo on mchp490a - CLUSTER-A", "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp490a.global-intra.net:8082/", "Migration Job Start: every day, 07:00 CET", "(runs ca. 5-6 hours)");
	var o2mcluBSet = de.sc.portal.o2m.makeMachine(paper, 1/*level*/, 3/*machIndex*/, 3/*#machinesOfLevel*/, "oracle2Mongo on mchp490a - CLUSTER-B", "linux", de.sc.portal.o2m.makeMachineO2M, "http://mchp490a.global-intra.net:9082/", "Migration Job Start: every day, 11:00 CET", "(runs ca. 5-6 hours)");
	
	var mTestSet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 1/*machIndex*/, 3/*#machinesOfLevel*/, "Mongo TEST DB on mchp407a"     , "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp407a.global-intra.net:38017/");
	var mCluASet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 2/*machIndex*/, 3/*#machinesOfLevel*/, "Mongo CLUSTER A DB on mchp363a", "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp363a.global-intra.net:27017/");
	var mCluBSet = de.sc.portal.o2m.makeMachine(paper, 2/*level*/, 3/*machIndex*/, 3/*#machinesOfLevel*/, "Mongo CLUSTER B DB on mchp363a", "linux", de.sc.portal.o2m.makeMachineMongo, "http://mchp363a.global-intra.net:37017/");

	var psTest = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 1/*machIndex*/, 4/*#machinesOfLevel*/, "pricingService TEST on mchp406a"     , "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp406a.global-intra.net:7070/");
	var psPRES = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 2/*machIndex*/, 4/*#machinesOfLevel*/, "pricingService PRE-STAGE on mchp489a", "linux", de.sc.portal.o2m.makeMachinePS, "http://mchp489a.global-intra.net:8080/");
	var psCLUA = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 3/*machIndex*/, 4/*#machinesOfLevel*/, "pricingService CLUSTER A", "linux"   , de.sc.portal.o2m.makeMachinePS, "http://mchp486a.global-intra.net:80/");
	var psCLUB = de.sc.portal.o2m.makeMachine(paper, 3/*level*/, 4/*machIndex*/, 4/*#machinesOfLevel*/, "pricingService CLUSTER B", "linux"   , de.sc.portal.o2m.makeMachinePS, "http://mchp486a.global-intra.net:8080/");
	
	graffle.setup(paper,
			{from:oracleSet, to:o2mtestSet, linecolor:"red", anitext: "daily TEST cronjob", ani:true},
			{from:oracleSet, to:o2mcluASet, linecolor:"red", anitext: "daily CLUSTER A cronjob", ani:true},
			{from:oracleSet, to:o2mcluBSet, linecolor:"red", anitext: "daily CLUSTER B cronjob", ani:true},
			{from:o2mtestSet, to:mTestSet, linecolor:"blue", ani:true},
			{from:o2mcluASet, to:mCluASet, linecolor:"blue", ani:true},
			{from:o2mcluBSet, to:mCluBSet, linecolor:"blue", ani:true},
			{from:mTestSet, to:psTest, linecolor:"red", ani:true},
			{from:mCluASet, to:psPRES, linecolor:"red", ani:true},
			{from:mCluASet, to:psCLUA, linecolor:"red", ani:true},
			{from:mCluBSet, to:psCLUB, linecolor:"red", ani:true}
		);
	
	{
		/*var h = $("#containertd").height();
		var resizef = function()
		{
			paper.setSize($("#containertd").width() - 9, h);
			//paper.setViewBox($("#container").width(), $("#container").height());
		};
		$(window).resize(resizef);
		resizef();*/
	}
};
de.sc.portal.o2m.makeMachine = function(paper, level, machineIndex, machineCountOfLevel, text, osImage, detailsF)
{
	if (de.sc.portal.o2m.allSets == null)
		de.sc.portal.o2m.allSets = paper.set();
	
	var colors1 = ["#f7fcf0","#e0f3db","#ccebc5","#a8ddb5","#7bccc4","#4eb3d3","#2b8cbe","#08589e"];
	var colors2 = ["#f7fcfd","#e0ecf4","#bfd3e6","#9ebcda","#8c96c6","#8c6bb1","#88419d","#6e016b"];

	paper.setStart();
	
	var x = ((paper.width / (machineCountOfLevel + 1)) * machineIndex) - (de.sc.portal.o2m.machinewidth / 2);
	
	var y = 50 + (level * (de.sc.portal.o2m.machineheight + 50));
	var width = de.sc.portal.o2m.machinewidth;
	var height = 0;
	var fillColor = "0-"+colors1[level]+"-"+colors2[level+1];//"0-#f00-#d00"/*red*/;
	var fillColorMouseOver = "1-"+colors2[level]+"-"+colors1[level+1];
	
	var machineRect = paper.rect(x, y, width, height, 15/*rounding*/)
						.attr("fill", fillColor)
						.animate({height:de.sc.portal.o2m.machineheight}, 1000, 'bounce')
						//.attr("href", "#http://mchp612a.global-intra.net/").attr("target", "_blank")
						.mouseover(function(){this.attr('r', 0 ).attr("fill", fillColorMouseOver);})
						.mouseout(function() {this.attr('r', 15).attr("fill", fillColor);});
	
	de.sc.portal.o2m.desc(paper, machineRect, text, Array.prototype.slice.call(arguments));
	
	var machineOS = paper.image("./img/"+osImage+".png", x, y, 32, 32);
	de.sc.portal.o2m.desc(paper, machineOS, "Operating system: "+osImage.upperFirst(true), Array.prototype.slice.call(arguments));
	
	detailsF.apply(machineRect, Array.prototype.slice.call(arguments));
	
	x = x + (de.sc.portal.o2m.machinewidth / 2);
	y = y + (de.sc.portal.o2m.machineheight + (text.indexOf("\n") > 1 ? 14 : 7));
	
	var machineText = paper.text(x, y, text);	//this is the def: .attr({"text-anchor":'middle'});
	
	var set = paper.setFinish();
	de.sc.portal.o2m.allSets.push(set);
	return set;
};
