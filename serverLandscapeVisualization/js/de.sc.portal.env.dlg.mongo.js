de.sc.portal.env.dlg.mongo = {};

de.sc.portal.env.dlg.mongo.mu = "104P116D116O112Q58H47L47M115T101E110H45Y115L111D97Y45I115S97C108R101V115J58W115I99S52U119G111R114J108P100N64F109G99Y104U112T51N54L51H97U46C103J108D111U98Q97M108H45T105K110V116N114K97T46N110C101R116H58E50T56X48N49A55D47";

de.sc.portal.env.dlg.mongo.dlg_height_original = 0;
de.sc.portal.env.dlg.mongo.div_height_original = 0;
de.sc.portal.env.dlg.mongo.tbl = null;
de.sc.portal.env.dlg.mongo.plot = null;

de.sc.portal.env.dlg.mongo.onDlgOpen = function()
{
	if(de.sc.portal.env.dlg.mongo.dlg_height_original === 0)
	{
		var tbar = $(".ui-dialog-title", $(this).parent());
		tbar.html("<img src='./img/mongo2.png' style='width:7px;position:absolute;margin-top:2px;' />&nbsp; &nbsp;"+ tbar.html()+"");
	}	
	de.sc.portal.env.dlg.mongo.dlg_height_original = $(this).css('height').replace(/px/, '');
	de.sc.portal.env.dlg.mongo.div_height_original = $("div:last-child", $(this)).css('height').replace(/px/, '');
};
de.sc.portal.env.dlg.mongo.onDlgClose = function()
{
  
};
de.sc.portal.env.dlg.mongo.onDlgResize = function()
{
	var dlg   = $(this);
	var dlg_h = dlg.css('height').replace(/px/,'');
	var div_h = (dlg_h * de.sc.portal.env.dlg.mongo.div_height_original) / de.sc.portal.env.dlg.mongo.dlg_height_original;
	$('#dlg_mongo_tabs', dlg).css('height', div_h - 10);
	var headerHeight = $('.ui-widget-header', dlg).height() * 2;
	$('.mongotab', dlg).css('height', (div_h - 10) - headerHeight);
	
};
de.sc.portal.env.dlg.mongo.show = function(button)
{
	$("#dlg_mongo").dialog('open');
	$("#dlg_mongo_tabs").tabs("option", "active", -1);
	$("#dlg_mongo_tabs").tabs("option", "active", 0);
};
de.sc.portal.env.dlg.mongo.isFirstTabActivated = function(ui)
{
	var next = ui.newTab.prev().size();
	if (next > 0)return false;
	
	if(de.sc.portal.env.dlg.mongo.plot === null)
	{
		var url = de.sc.portal.env.dlg.mongo.mu.d()+"listDatabases";
		$.ajax
		({
			url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(url)) : "_listDatabases"), dataType:"json"
		})
		.success(function(jsondata)
		{
			var options =
			{
				title: 'Mongo DBs',
				animate: true,
				animateReplot: true,
				stackSeries: true,
		
				seriesDefaults:
				{
					renderer:$.jqplot.DonutRenderer,
					rendererOptions:
					{
						showDataLabels: true,
						dataLabels: 'value',
						sliceMargin: 2,
						startAngle: -90,
						innerDiameter: 5,
						ringMargin: 5,
						shadow: true,
						showMarker: true,
						markerOptions: { show: true },
						pointLabels: { show: true, location: 's' },
						smooth: true,
						animation: { show: true, speed: 2500 },
						shadowDepth:11,
					numberRows:3,
					numberColumns:3,
						
						//dataLabelThreshold:0,
						dataLabels : 'percent'	//‘label’, ‘value’, ‘percent’
					}
				},
				highlighter:
				{
					show: false,
					sizeAdjust: 7.5
				},
				cursor:
				{
					show: false,
					zoom: true,
					showTooltip: true
				},
				legend:
				{
					renderer: $.jqplot.DonutLegendRenderer,
					//renderer: $.jqplot.EnhancedLegendRenderer,
					numberRows:3,
					numberColumns:3,
					show: true,
					placement: 'outsideGrid',
					location: 'e'
				},
				grid:
				{
					background: 'white'
				}
			};
			
			var data = new Array();
			{
				var dbs = jsondata["databases"];
				var sum=0;
				for(var i=0;i<dbs.length;i++)
				{
					var db = dbs[i];
					var sizeOnDisk = de.sc.portal.env.dlg.mongo.getSizeAsReadableString(db["sizeOnDisk"]);
					var size = db["empty"] ? " (is empty)" : " (size: "+sizeOnDisk+")";
					var thisdata = new Array();
					thisdata.push(db["name"] + (db["empty"] ? " (is empty)" : ""));
					thisdata.push(db["sizeOnDisk"]);
					thisdata.push(size);
					data.push(thisdata);
					sum += db["sizeOnDisk"];
				}
				options.title = options.title + " (" +de.sc.portal.env.dlg.mongo.getSizeAsReadableString(sum)+")";
			}
			
			
		   de.sc.portal.env.dlg.mongo.plot = jQuery.jqplot ('mongodbschart', [data], options);
		
		   $('div.mongodbschart-container').resizable({delay: 20});
		   $('div.mongodbschart-container').bind('resize', function(event, ui)
		   {
				de.sc.portal.env.dlg.mongo.plot.replot();
		   });
		   
			$('#mongodbschart').bind('jqplotDataHighlight', function (ev, seriesIndex, pointIndex, data)
			{
				$('#mongodbschartinfo').html(data[0]+" "+data[2]);
		        var mouseX = ev.pageX;
		        var mouseY = ev.pageY;
		        
		        var o = $("#dlg_mongo").offset();
		        mouseX -= o.left;
		        mouseY -= o.top;
		        
		        var cssObj =
		        {
		                  position : 'absolute',
		                  'font-weight' : 'bold',
		                  left : mouseX + 'px',
		                  top : mouseY + 'px',
		                  color:'black'
		        };
		        $('#mongodbschartinfo').css(cssObj);
			});
			$('#mongodbschart').bind('jqplotDataUnhighlight', function (ev, seriesIndex, pointIndex, data)
			{
				$('#mongodbschartinfo').html("");
			});
			
			$(".jqplot-table-legend", "#dlg_mongo").css("text-align","left").css("background-color","white").css("font-size","9px");
			$("table.jqplot-table-legend", "#dlg_mongo").css("top","0px");
		});
	}
	
	return true;
};
de.sc.portal.env.dlg.mongo.isLastTabActivated = function(ui)
{
	var next = ui.newTab.next().size();
	if (next > 0)return false;
	
	$("#cols, #fields","#dlg_mongo_tabs").html(" ");
	var select = $("#dbs","#dlg_mongo_tabs");
	select.next().show();
	
	var url = de.sc.portal.env.dlg.mongo.mu.d()+"listDatabases";
	
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(url)) : "_listDatabases"), dataType:"json"
	})
	.success(function(data)
	{
		var dbs = data["databases"];
		
		if(select.size() < 1)
		{
			de.sc.log("cisLastTabActivated:\n!select"+ui.newTab.html(), de.sc.ERR);
			return;
		}
		select.html("<option></option>");
		for(var i=0;i<dbs.length;i++)
		{
			var db = dbs[i];
			var sizeOnDisk = de.sc.portal.env.dlg.mongo.getSizeAsReadableString(db["sizeOnDisk"]);
			var size = db["empty"] ? " (is empty)" : " (size: "+sizeOnDisk+")";
			var o = new Option(db["name"]+size, db["name"], false, false);
			select[0][select[0].options.length] = o;
		}
		select.next().hide();
	})
	.error(function(xhr, statusmsg, err)
	{
		de.sc.log("\ncisLastTabActivated:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});
	
	return true;
};
de.sc.portal.env.dlg.mongo.getSizeAsReadableString = function(sizeAsNumber)
{
	if((sizeAsNumber === null) || (sizeAsNumber === 0) || (sizeAsNumber === ""))return sizeAsNumber;
	if(sizeAsNumber < 1024)
		return sizeAsNumber + " bytes";
	if(sizeAsNumber < 			1024*1024)
		return (sizeAsNumber / 	1024).toFixed(2) + " kb";
	if(sizeAsNumber < 			1024*1024*1024)
		return (sizeAsNumber / (	1024*1024)).toFixed(2) + " mb";
	if(sizeAsNumber < 			1024*1024*1024*1024)
		return (sizeAsNumber / (	1024*1024*1024)).toFixed(2) + " gb";
	if(sizeAsNumber < 			1024*1024*1024*1024*1024)
		return (sizeAsNumber / (	1024*1024*1024*1024)).toFixed(2) + " tb";
	
	de.sc.log("\ngetSizeAsReadableString:\nunexpected nr:"+sizeAsNumber, de.sc.WRN);
	return sizeAsNumber;
};
de.sc.portal.env.dlg.mongo.onSelectCols = function(eSelect)
{
	$("#fields","#dlg_mongo_tabs").html(" ");
	var db  = $("#dbs","#dlg_mongo_tabs")[0].options[$("#dbs","#dlg_mongo_tabs")[0].selectedIndex].value;
	if(de.sc.isempty(db))return;
	var col = eSelect.options[eSelect.selectedIndex].value;
	if(de.sc.isempty(col))return;
	
	var select = $("#fields","#dlg_mongo_tabs");
	select.next().show();
	var url = de.sc.portal.env.dlg.mongo.mu.d()+db+"/"+col+"/?limit=1";
	
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get_with_params.cgi?"+escape(url)) : "_items"), dataType:"json"
	})
	.success(function(data)
	{
		var item = data["rows"][0];
		if (select.size() < 1)
		{
			de.sc.log("onSelectCols:\n!select", de.sc.ERR);
			return;
		}
		select.html("<option></option>");
		for(var attrName in item)
		{
			if(attrName.indexOf('_') === 0)continue;
			//var attrValue = item[attrName];
			var o = new Option(attrName, attrName, false, false);
			select[0][select[0].options.length] = o;
		}
		select.next().hide();
	})
	.error(function(xhr, statusmsg, err)
	{
		select.next().hide();
		de.sc.log("\nonSelectCols:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});	
};
de.sc.portal.env.dlg.mongo.onSearch = function(searchB)
{
	var db  = $("#dbs" 	 ,"#dlg_mongo_tabs")[0].options[$("#dbs"   ,"#dlg_mongo_tabs")[0].selectedIndex].value;
	var col = $("#cols"	 ,"#dlg_mongo_tabs")[0].options[$("#cols"  ,"#dlg_mongo_tabs")[0].selectedIndex].value;
	var fld = $("#fields","#dlg_mongo_tabs")[0].options[$("#fields","#dlg_mongo_tabs")[0].selectedIndex].value;
	
	if(de.sc.isempty(db) || de.sc.isempty(col))
	{
		alert("Please choose an entry in the above dropdowns.");
		return;
	}
	if(!de.sc.isempty(fld) && de.sc.isempty($("#filter","#dlg_mongo_tabs")[0].value))
	{
		alert("Please enter a search expression for the field '"+fld+"',\nor\nclear the Field dropdown.");
		return;
	}
	
	$(searchB).next().show();
	
	if (de.sc.portal.env.dlg.mongo.tbl !== null)
		de.sc.portal.env.dlg.mongo.tbl.destroy();
	de.sc.portal.env.dlg.mongo.tbl = null;
	$("#dlg_mongo_tabs_search_resultlist, #dlg_mongo_tabs_search_resultssummary","#dlg_mongo_tabs").html(" ");
	
	var query = $("#filter","#dlg_mongo_tabs")[0].value;
	query = de.sc.isempty(query) ? "" : "{"+fld+":/"+query+"/i}";
	var url = de.sc.portal.env.dlg.mongo.mu.d()+db+"/$cmd/?filter_eval=function(){return%20db."+col+".find("+query+").limit(50).toArray()}&limit=1";
	
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get_with_params.cgi?"+escape(url)) : "_mongo_query_resultlist"), dataType:"json"
	})
	.success(function(data)
	{
		var hits = data["rows"][0]["retval"];
		
		{
			$("#dlg_mongo_tabs_search_resultssummary","#dlg_mongo_tabs").html(" search time: "+data["millis"]+" ms. Hits: "+hits.length);
		}
		
		if(hits.length < 1)
		{
			$("#dlg_mongo_tabs_search_resultlist","#dlg_mongo_tabs").html(" no hits");
			$(searchB).next().hide();
			return;
		}
		var hit = null;
		var attrName = null;
		{
			hit = hits[0];
			var ths = "";
			for(attrName in hit)
			{
				if(attrName.indexOf('_') === 0)continue;
				ths += "<th>"+attrName+"</th>";
			}

			var tble = '<table id="dlg_mongo_tabs_search_resultlisttbl" class="display" border="1" style="width:100%;border:gray 1px groove; padding:3px; margin:3px;" cellpadding="3px" cellspacing="3px">'+
		        			'<thead>'+
		            			'<tr>'+
		            				ths+
		            			'</tr>'+
		        			'</thead>'+
		        			'<tfoot>'+
		            			'<tr>'+
		            				ths+
		            			'</tr>'+
		        			'</tfoot>'+
		        			'<tbody>'+
		       				'</tbody>'+
						'</table>';
			
			$("#dlg_mongo_tabs_search_resultlist","#dlg_mongo_tabs").html(tble);
			
			de.sc.portal.env.dlg.mongo.tbl = $("#dlg_mongo_tabs_search_resultlisttbl", "#dlg_mongo_tabs").DataTable({
    			paging:    false,
 				searching: true,
    			ordering:  true,
    			info:	   true,
    			order: [[ 1, "desc" ]]
			});
		}
		
		for(var i=0;i<hits.length;i++)
		{
			hit = hits[i];
			var ahit = new Array();
			for(attrName in hit)
			{
				if(attrName.indexOf('_') === 0)continue;
				var attrValue = hit[attrName];
				ahit.push(attrValue);
			}
			//TODO: check if draw could be called only once at the end of the loop
			de.sc.portal.env.dlg.mongo.tbl.row.add(ahit).draw();
		}
		$(searchB).next().hide();
	})
	.error(function(xhr, statusmsg, err)
	{
		$(searchB).next().hide();
		de.sc.log("\ncisLastTabActivated:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});
};
de.sc.portal.env.dlg.mongo.onSelectDBs = function(eSelect)
{
	$("#cols, #fields","#dlg_mongo_tabs").html(" ");
	var db = eSelect.options[eSelect.selectedIndex].value;
	if(de.sc.isempty(db))return;
	
	var select = $("#cols","#dlg_mongo_tabs");
	select.next().show();
	var url = de.sc.portal.env.dlg.mongo.mu.d()+db+"/$cmd/?filter_$eval=function(){return%20db.getCollectionNames()}&limit=1";
	
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get_with_params.cgi?"+escape(url)) : "_getColNames"), dataType:"json"
	})
	.success(function(data)
	{
		var cols = data["rows"][0]["retval"];
		if (select.size() < 1)
		{
			de.sc.log("onSelectDBs:\n!select"+ui.newTab.html(), de.sc.ERR);
			return;
		}
		select.html("<option></option>");
		for(var i=0;i<cols.length;i++)
		{
			var col = cols[i];
			var tit = col.replace(/^mongo/, "").replace(/Impl$/, "");
			var o = new Option(tit, col, false, false);
			select[0][select[0].options.length] = o;
		}
		select.next().hide();
	})
	.error(function(xhr, statusmsg, err)
	{
		select.next().hide();
		de.sc.log("\ncisLastTabActivated:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});
};
de.sc.portal.env.dlg.mongo.onTabActivate = function(event, ui)
{
	if(de.sc.portal.env.dlg.mongo.isLastTabActivated(ui))
	{
		return;
	}
	if(de.sc.portal.env.dlg.mongo.isFirstTabActivated(ui))
	{
		return;
	}

	var sTabText = $.trim(ui.newTab.html().replace(/<.*?>/g, ""));
	var url = de.sc.portal.env.dlg.mongo.mu.d()+sTabText.replace(/\s*/g, "").upperFirst(false);
	
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(url)) : "_hostInfo"), dataType:"json"
	})
	.success(function(data)
	{
		var tbl = de.sc.portal.env.dlg.mongo.maketable(data, 0);
		ui.newPanel.html("<div>"+tbl+"</div>");
	})
	.error(function(xhr, statusmsg, err)
	{
		de.sc.log("\nconTabActivate:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});
};
de.sc.portal.env.dlg.mongo.maketable = function(data, iRecDepth)
{
	var s = "";
	for(var attrName in data)
	{
		if(""+attrName == "0")break;
		
		var attrValue = data[attrName];

		if((typeof attrValue !== 'string') && attrValue.length)
		{
			for(var i=0;i<attrValue.length;i++)
			{
				s += de.sc.portal.env.dlg.mongo.maketableentry(iRecDepth+1, attrName+" ("+(i+1)+")", attrValue[i]);
			}
		}
		else
		{
			s += de.sc.portal.env.dlg.mongo.maketableentry(iRecDepth+1, attrName, attrValue);
		}
	}
	
	return s;
};
de.sc.portal.env.dlg.mongo.maketableentry = function(iRecDepth, attrName, attrValue)
{
	var s = " <div class='treeentry e"+iRecDepth+"' "+(iRecDepth > 1 ? "style='display:none;'" : "")+">  <img src='./img/treemarker.png' />";
	
	var hasChildren = true;
	if((typeof attrValue === 'string') || (typeof attrValue === 'number') || (typeof attrValue === 'boolean'))
	{
		hasChildren = false;
		if(typeof attrValue === 'number')
		{
			if(attrName == "$date")
			{
				attrValue = new Date(attrValue);
			}
			else
			{
				attrValue = attrValue.formatNumber();
			}
		}
	}
	if (hasChildren)
	{
		s += " <a href='#' class='awithplusminus onexpand'><img src='./img/plus.gif' /><img src='./img/minus.gif' style='display:none;' /></a> ";
	}
	else
	{
		s += " <img src='./img/spacer.gif' style='width:9px;' /> ";
	}
	
	s += " <span class='attrname'>"+attrName+(hasChildren ? '' : ': ')+"</span> ";
	
	if(!hasChildren)
	{
		s += " <span class='attrvalue'>"+attrValue+"</span>";
	}
	else
	{
		s += de.sc.portal.env.dlg.mongo.maketable(attrValue, iRecDepth+1);
	}
	
	s += "</div>";
	
	return s;
};