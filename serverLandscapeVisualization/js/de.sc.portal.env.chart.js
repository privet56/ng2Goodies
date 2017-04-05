de.sc.portal.env.chart = {};

de.sc.portal.env.chart.makeLiveSessionsChart = function(servers)
{
	var data8080 = [0];
	var data9090 = [0];
	
	var options =
	{
		animate: false,
		animateReplot: false,
		stackSeries: false,
		title: 'Live Sessions',

		axes:
		{
			xaxis:
			{
				min: 1,
				max: 21,
				numberTicks: 5,
				label: "Requests",
				autoscale:true
			 },
			yaxis:
			{
				min: -1,
				max: 19,
				numberTicks: 6,
				label: "# of open Sessions",
				autoscale:true,
            	labelRenderer: $.jqplot.CanvasAxisLabelRenderer,	//can rotate label
            	labelOptions:
            	{
                	fontFamily:'Helvetica',
                	fontSize: '12pt'
            	},
				tickOptions:
				{
					formatString:'%.0f'	//without decimal places
				}
			}
		},
		seriesDefaults:
		{
			showMarker: true,
			rendererOptions: {smooth: true}
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
			background: 'lightgreen'
		},
		series:
		[
			{label:'clustera'},
			{label:'clusterb'}
		]
	};
	
   var plot = jQuery.jqplot ('livesessionsserverchart', [data8080, data9090], options);

   $('div.livesessionschart-container').resizable({delay: 20});
   $('div.livesessionschart-container').bind('resize', function(event, ui)
   {
		plot.replot();
   });
   
   	var mod_cluster_manager_10001 = servers[0][0].getModClusterManagerURL();
   	var mod_cluster_manager_20001 = servers[1][0].getModClusterManagerURL();
   
   	var bFirstAjaxCall = true;
   
	$(document).on(de.sc.portal.env.msg.MOD_CLUSTER_MANAGER, function(msg_data)
	{
		var getSessionCount = function(html)
		{
			html = html.replace(/:/g, "_");
			
			var rePattern = /Num sessions_\s*(\d+)/gi;
			var arrMatch = null;
			var iSessionCount = 0;
			while (arrMatch = rePattern.exec(html))
			{
				iSessionCount += Number(arrMatch[1]);
			}
			return iSessionCount;
		};
			
		var mod_cluster_manager_10001_sessionCount = getSessionCount(msg_data["clusters"][0]["content"]);
		var mod_cluster_manager_20001_sessionCount = getSessionCount(msg_data["clusters"][1]["content"]);
			
		while(data8080.length > 19){data8080.shift();}
		while(data9090.length > 19){data9090.shift();}
		
		var bWasFirstAjaxCall = bFirstAjaxCall;
		
		if(bFirstAjaxCall)
		{
			bFirstAjaxCall = false;
			data8080[0] = data8080[1] = mod_cluster_manager_10001_sessionCount;
			data9090[0] = data9090[1] = mod_cluster_manager_20001_sessionCount;
		}
		else
		{
			data8080.push(mod_cluster_manager_10001_sessionCount);
			data9090.push(mod_cluster_manager_20001_sessionCount);						
		}
		
		//console.log("bFirstAjaxCall:"+bWasFirstAjaxCall+" data8080.len:"+data8080.length+" mod_cluster_manager_10001_sessionCount:"+mod_cluster_manager_10001_sessionCount+" mod_cluster_manager_20001_sessionCount:"+mod_cluster_manager_20001_sessionCount);
		
		plot.destroy();

		var max = de.sc.getMaxOfArraysElements(data8080, data9090);
		options.axes.yaxis.max = max + 9;
		
		$('#livesessionsserverchart').empty();	//avoid memory leak
		plot = $.jqplot('livesessionsserverchart', [data8080, data9090], options);
	});
};
de.sc.portal.env.chart.makeDonutChart = function(servers)
{
	var options =
	{
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
				animation: { show: true, speed: 2500 }
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
			renderer: $.jqplot.EnhancedLegendRenderer,
			show: true,
			placement: 'outsideGrid',
			location: 'e'
		},
		grid:
		{
			background: 'lightgreen'
		}
	};
	
	var dataserver = new Array();
	var datawars   = new Array();
	{
	  var clustera = servers[0];
	  for(var i=4;i<clustera.length;i++)
	  {
	  	var server = clustera[ i];
	  	var data = new Array();
	  	data.push("mchp"+server.iMachineIndex);
	  	data.push(server.iRAM);
	  	dataserver.push(data);

	  	var ram = server.iRAM / 4;
	  	
	  	jbossasss = new Array();jbossasss.push("mchp"+server.iMachineIndex+": clustera-sss");jbossasss.push(ram);datawars.push(jbossasss); 
	  	jbossase  = new Array();jbossase.push("mchp"+server.iMachineIndex+": clustera-se");  jbossase.push(ram);datawars.push(jbossase);
	  	jbossbsss = new Array();jbossbsss.push("mchp"+server.iMachineIndex+": clusterb-sss");jbossbsss.push(ram);datawars.push(jbossbsss);
	  	jbossbse  = new Array();jbossbse.push("mchp"+server.iMachineIndex+": clusterb-se");  jbossbse.push(ram);datawars.push(jbossbse);
	  }
	}
	
   var plot = jQuery.jqplot ('donutserverchart', [datawars, dataserver], options);

   $('div.donutchart-container').resizable({delay: 20});
   $('div.donutchart-container').bind('resize', function(event, ui)
   {
		plot.replot();
   });
   
	$('#donutserverchart').bind('jqplotDataHighlight', function (ev, seriesIndex, pointIndex, data)
	{
		$('#donutinfo1').html(data[0]+": "+data[1]+" GB RAM");
		$('#donutinfo2').html(data[0]+": "+data[1]+" GB RAM");
        var mouseX = ev.pageX;
        var mouseY = ev.pageY;
        var cssObj =
        {
                  'position' : 'absolute',
                  'font-weight' : 'bold',
                  'left' : mouseX + 'px',
                  'top' : mouseY + 'px',
                  'color':'white'
        };
        $('#donutinfo1').css(cssObj);
	});
	$('#donutserverchart').bind('jqplotDataUnhighlight', function (ev, seriesIndex, pointIndex, data)
	{
		$('#donutinfo1').html("");
		$('#donutinfo2').html("");
	});
};
de.sc.portal.env.chart.makechart = function(servers)
{  
  var datamax = 3;
  var datas = new Array();
  var ticks = new Array();
  {
	  var clustera = servers[0];
	  
	  for(var i=4;i<clustera.length;i++)
	  {
	  	var data = new Array();
	  	datas.push(data);
	  }
	  for(var iclustera=4;iclustera<clustera.length;iclustera++)
	  {
	  	var server = clustera[ iclustera];
	  	var serverdata = datas[iclustera - 4];
	  	
	  	var ram = (server.iRAM / 4);
	  	
	  	serverdata.push(ram);	//clustera-sss
	  	serverdata.push(ram);	//clustera-se
	  	serverdata.push(ram);	//clusterb-sss
	  	serverdata.push(ram);	//clusterb-se
	  	
	  	datamax = server.iRAM;

		ticks.push("mchp"+server.iMachineIndex);
	  }
  }
  
  var options =
  {
	//fillBetween, trendline, 
	animate: true,
	animateReplot: true,
	title: 'SSS / SE Servers',
	stackSeries: true,
	seriesDefaults:
	{
		shadow: true,
		renderer:$.jqplot.BarRenderer,
		showMarker: true,
		markerOptions: { show: true },
		pointLabels: { show: true, location: 's' },
		rendererOptions:
		{
			smooth: true,
			barMargin: 15,
			animation: { show: true, speed: 2500 }
		}
	},
	series:
	[
		{label:'clustera, jbossprod1'},
		{label:'clustera, jbossprod2'},
		{label:'clusterb, jbossprod1'},
		{label:'clusterb, jbossprod2'}
	],
	axes:
	{
		xaxis:
		{
			renderer: $.jqplot.CategoryAxisRenderer,
			ticks: ticks,
			label: "Server",
			autoscale: true,
			tickRenderer: $.jqplot.CanvasAxisTickRenderer,
			tickOptions:
			{
				showGridline: false,
				angle: -30
			}
		},
		yaxis:
		{
			label: "RAM",
			max: datamax + 3,
			min: 0,
			autoscale: true,
			numberTicks: 5,
			tickRenderer: $.jqplot.AxisTickRenderer,
			tickOptions:
			{
				formatString:'%d GB'
			}
		}
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
		background: 'lightgreen'
	},
	canvasOverlay:
	{
		show: true,
		objects:
		[
			{
				dashedHorizontalLine:
				{
					y: datamax + 1,
					lineWidth: 2,
					color: 'rgb(0, 0, 255)',
					shadow: false,
					dashPattern: [8, 16],
					lineCap: 'round'
				}
			}
		]
	}
  };
  
   var plot = $.jqplot ('serverchart', datas, options);
   $('#serverchart').bind('jqplotDataClick',	function (ev, seriesIndex, pointIndex, data)
   {
		//$('#serverchart_info').html('series: ' + seriesIndex + ', point: '+pointIndex+', data: '+data);
   });
 
   $('div.chart-container').resizable({delay: 20});
   $('div.chart-container').bind('resize', function(event, ui)
   {
		plot.replot();
   });
};
