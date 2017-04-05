de.sc.portal.env.dlg.jmx = {};

de.sc.portal.env.dlg.jmx.plot = null;
de.sc.portal.env.dlg.jmx.dlg_height_original = 0;
de.sc.portal.env.dlg.jmx.div_height_original = 0;

de.sc.portal.env.dlg.jmx.onDlgOpen = function()
{
	if(de.sc.portal.env.dlg.jmx.dlg_height_original === 0)
	{
		var tbar = $(".ui-dialog-title", $(this).parent());
		tbar.html("<img src='./img/java_small.png' style='width:7px;position:absolute;margin-top:2px;' />&nbsp; &nbsp;"+ tbar.html()+"");
	}	
	de.sc.portal.env.dlg.jmx.dlg_height_original = $(this).css('height').replace(/px/, '');
	de.sc.portal.env.dlg.jmx.div_height_original = $("div:last-child", $(this)).css('height').replace(/px/, '');
};
de.sc.portal.env.dlg.jmx.onDlgClose = function()
{
	$("#jmxtab-2").empty();
};
de.sc.portal.env.dlg.jmx.onTabActivate = function(event, ui)
{
	var next = ui.newTab.next().size();
	if (next === 0)	//=last tab
	{
		de.sc.portal.env.dlg.jmx.onLastTabActivate(event, ui);
	}
	else
	{
		de.sc.portal.env.dlg.jmx.onFirstTabActivate(event, ui);
	}
};
de.sc.portal.env.dlg.jmx.onDlgResize = function()
{
	var dlg   = $(this);
	var dlg_h = dlg.css('height').replace(/px/,'');
	var div_h = (dlg_h * de.sc.portal.env.dlg.jmx.div_height_original) / de.sc.portal.env.dlg.jmx.dlg_height_original;
	$('#dlg_jmx_tabs', dlg).css('height', div_h - 10);
	var headerHeight = $('.ui-widget-header', dlg).height() * 2;
	$('.jmxtab, #livememchart', dlg).css('height', (div_h - 10) - headerHeight);
	
	$('#livememchart', dlg).css('width', $('#dlg_jmx_tabs').css('width').replace(/px/,'') - 39);
	
	de.sc.portal.env.dlg.jmx.plot.replot();
	
};
de.sc.portal.env.dlg.jmx.show = function(button)
{
	$("#dlg_jmx").dialog('open');
	$("#dlg_jmx_tabs").tabs("option", "active", -1);
	$("#dlg_jmx_tabs").tabs("option", "active", 0);
};
de.sc.portal.env.dlg.jmx.makeLiveMemChart = function(servers)
{
	var bOnlyHeapmemoryUsage = true;
	var dataHeapMemoryUsage = [0];
	var dataNonHeapMemoryUsage = [0];
	
	var options =
	{
		animate: false,
		animateReplot: false,
		stackSeries: false,
		title: 'Memory usage',

		axes:
		{
			xaxis:
			{
				min: 1,
				max: 21,
				numberTicks: 21,
				label: "Read",
				autoscale:true
			 },
			yaxis:
			{
				min: 0,
				max: 1000,
				numberTicks: 11,
				label: "Memory Usage",
				autoscale:true,
            	labelRenderer: $.jqplot.CanvasAxisLabelRenderer,	//can rotate label
            	labelOptions:
            	{
                	fontFamily:'Helvetica',
                	fontSize: '12pt'
            	},
				tickOptions:
				{
					formatString:'%.0f'	//without decimal places		//TODO: convert to MB
				}				
			}
		},
		seriesDefaults:
		{
			showMarker: false,		//booble
			rendererOptions: {smooth: true},
        	lineWidth: 2.5, 		// Width of the line in pixels.
        	//color: '#00FF00',    	// CSS color spec to use for the line.  Determined automatically.
        	seriesColors: [ '#0066FF' , '#00FF00' ]			
		},
		highlighter:
		{
			show: true,
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
			renderer: $.jqplot.EnhancedLegendRenderer,
			show: true,
			placement: 'outsideGrid',
			location: 'ne'
		},
		grid:
		{
		   	drawGridLines: true,        // wether to draw lines across the grid or not.
		    gridLineColor: 'green',   	// *Color of the grid lines.
		    background: 'black',    	// CSS color spec for background color of grid.
		    borderColor: 'green',	   	// CSS color spec for border around grid.
		    borderWidth: 2.0,           // pixel width of border around grid.
		    shadow: true,               // draw a shadow for grid.
		    shadowAngle: 45,            // angle of the shadow.  Clockwise from x axis.
		    shadowOffset: 1.5,          // offset from the line of the shadow.
		    shadowWidth: 3,             // width of the stroke for the shadow.
		    shadowDepth: 3,             // Number of strokes to make when drawing shadow. Each stroke offset by shadowOffset from the last.
		    shadowAlpha: 0.07,          // Opacity of the shadow
		    renderer: $.jqplot.CanvasGridRenderer,  // renderer to use to draw the grid.
		    rendererOptions: {}         // options to pass to the renderer.  Note, the default CanvasGridRenderer takes no additional options.
		},
		seriesColors: [ '#00FF00' , '#0066FF' ],
		series: bOnlyHeapmemoryUsage ? [{label:'HeapMemUsage'}] : [ {label:'HeapMemUsage'}, {label:'NonHeapMemUsage'} ]
		//legend: { visible: false },
	};

   	de.sc.portal.env.dlg.jmx.plot = jQuery.jqplot ('livememchart', bOnlyHeapmemoryUsage ? [dataHeapMemoryUsage] : [dataHeapMemoryUsage, dataNonHeapMemoryUsage], options);

   	var bFirstAjaxCall = true;
   	
   	window.setInterval(function()
   	{
   		var url = "http://mchp490a.global-intra.net:9080/jmx-monitoring/read/java.lang:type=Memory";
		$.ajax
		({
			url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(url)) : "_java.lang type=Memory"), dataType:"json"
		})
		.success(function(data)
		{
			heapMemoryUsage 	= data["value"]["HeapMemoryUsage"]["used"];
			nonHeapMemoryUsage 	= data["value"]["NonHeapMemoryUsage"]["used"];
			
			while(dataHeapMemoryUsage.length > 19){dataHeapMemoryUsage.shift();}
			while(dataNonHeapMemoryUsage.length > 19){dataNonHeapMemoryUsage.shift();}
			
			var bWasFirstAjaxCall = bFirstAjaxCall;
			
			if(bFirstAjaxCall)
			{
				bFirstAjaxCall = false;
				dataHeapMemoryUsage[0] 	  = dataHeapMemoryUsage[1]    = heapMemoryUsage;
				dataNonHeapMemoryUsage[0] = dataNonHeapMemoryUsage[1] = nonHeapMemoryUsage;
			}
			else
			{
				dataHeapMemoryUsage.push(heapMemoryUsage);
				dataNonHeapMemoryUsage.push(nonHeapMemoryUsage);						
			}
			
			//console.log("bFirstAjaxCall:"+bWasFirstAjaxCall+" data8080.len:"+data8080.length+" mod_cluster_manager_10001_sessionCount:"+mod_cluster_manager_10001_sessionCount+" mod_cluster_manager_20001_sessionCount:"+mod_cluster_manager_20001_sessionCount);
			
			de.sc.portal.env.dlg.jmx.plot.destroy();
			var max = null;
	
			if(bOnlyHeapmemoryUsage)
			{
				max = de.sc.getMaxOfArraysElements(dataHeapMemoryUsage);
				var min = de.sc.getMinOfArraysElements(dataHeapMemoryUsage);
				options.axes.yaxis.max = max + (max / 10);
				options.axes.yaxis.min = min - (min / 10);
			}
			else
			{
				max = de.sc.getMaxOfArraysElements(dataHeapMemoryUsage, dataNonHeapMemoryUsage);
				options.axes.yaxis.max = max + (max / 10);
				//TODO: set min(or better not to lie and let it 0?)
			}
			
			$('#livememchart').empty();	//avoid memory leak
			de.sc.portal.env.dlg.jmx.plot = $.jqplot('livememchart', bOnlyHeapmemoryUsage ? [dataHeapMemoryUsage] : [dataHeapMemoryUsage, dataNonHeapMemoryUsage], options);
		})
		.error(function(xhr, statusmsg, err)
		{
			de.sc.log("\ndlg.jmx:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\n'"+url+"'", de.sc.WRN);
		});	

   	}, 5000);
};
de.sc.portal.env.dlg.jmx.onFirstTabActivate = function(event, ui)
{
	//TODO:
};
de.sc.portal.env.dlg.jmx.onLastTabActivate = function(event, ui)
{
	var dlg_jmx_details = $("#jmxtab-2");
	dlg_jmx_details.html(" ");
	
	var urls = ["", "Memory", "Threading", "OperatingSystem", "Runtime", "ClassLoading", "Compilation"];
	
	for(var i=0;i<urls.length;i++)
	{
		if((window.location.href.indexOf("http") !== 0) && (i > 1))break;
		
		var url = "http://mchp490a.global-intra.net:9080/jmx-monitoring/" + (de.sc.isempty(urls[i]) ? "" : ("read/java.lang:type="+urls[i]));
		var type = de.sc.isempty(urls[i]) ? "[configuration]" : urls[i];
		
		(function(url, type, dlg_jmx_details)
		{
			$.ajax
			({
				url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(url)) : "_java.lang type=Runtime"), dataType:"json"
			})
			.success(function(data)
			{
				var tbl = de.sc.portal.env.dlg.jmx.maketable(data, 0, type);
				dlg_jmx_details.html(dlg_jmx_details.html()+"<div>"+tbl+"</div>");
			})
			.error(function(xhr, statusmsg, err)
			{
				de.sc.log("\ncheckavailability:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+url+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
			});	
		})(url, type, dlg_jmx_details);
	}
};
de.sc.portal.env.dlg.jmx.maketable = function(data, iRecDepth, type)
{
	var s = "";
	for(var attrName in data)
	{
		if(""+attrName == "0")break;
		
		if((iRecDepth === 0) && (attrName != "value"))continue;
		
		var attrValue = data[attrName];

		if((typeof attrValue !== 'string') && attrValue.length)
		{
			for(var i=0;i<attrValue.length;i++)
			{
				s += de.sc.portal.env.dlg.jmx.maketableentry(iRecDepth+1, attrName+" ("+(i+1)+")", attrValue[i], type);
			}
		}
		else
		{
			s += de.sc.portal.env.dlg.jmx.maketableentry(iRecDepth+1, attrName, attrValue, type);
		}
	}
	
	return s;
};
de.sc.portal.env.dlg.jmx.maketableentry = function(iRecDepth, attrName, attrValue, type)
{
	var s = " <div class='treeentry e"+iRecDepth+"' "+(iRecDepth > 1 ? "style='display:none;'" : "")+">  <img src='./img/treemarker.png' />";
	
	var hasChildren = true;
	if((typeof attrValue === 'string') || (typeof attrValue === 'number') || (typeof attrValue === 'boolean'))
	{
		hasChildren = false;
		if(typeof attrValue === 'number')
		{
			if((attrName == "$date") || ((attrName == "timestamp")))
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
	
	var attrName2Display = attrName;
	if((iRecDepth == 1) && (attrName == "value"))
		attrName2Display = type;
	
	s += " <span class='attrname'>"+attrName2Display+(hasChildren ? '' : ': ')+"</span> ";
	
	if(!hasChildren)
	{
		s += " <span class='attrvalue'>"+attrValue+"</span>";
	}
	else
	{
		s += de.sc.portal.env.dlg.jmx.maketable(attrValue, iRecDepth+1);
	}
	
	s += "</div>";
	
	return s;
};