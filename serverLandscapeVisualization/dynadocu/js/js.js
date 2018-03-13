$(document).ready(function()
{
	//alert(encodeURIComponent('##%*X3MT'));
	$('body').on('close.bs.alert', function(e) {
        e.preventDefault();
        e.stopPropagation();
        $(e.target).slideUp(1222);
    });
    $("*").each(function(index)
	{
		var e = $(this);
		if((e[0].nodeName.toLowerCase() != 'a') && (e.children().length < 1))
		{
			var text = $.trim($(this).text());
			if((text.indexOf("http") == 0) && !text.match(/\s/g))
			{
				var cl_softcon = ((text.toLowerCase().indexOf('softcon') > -1) || (text.toLowerCase().indexOf('nagarro') > -1)) ? 'softcon' : 'notsoftcon';
				var displayText = text.length > 99 ? text.substring(0, 99)+"..." : text;
				e.html("<a href='"+text+"' target=_new class='lnk "+cl_softcon+"' data-toggle='tooltip' data-placement='top' title='"+text+"'>"+displayText+"</a>");
			}
		}
		e.tooltip();
	});
	var ie = (window.navigator.msSaveOrOpenBlob != undefined) && (window.navigator.userAgent.toLowerCase().indexOf("edge") < 0);
	if( ie)
	{
		$(".not4ie").hide();
		$(".only4ie").show();
	}
	else
	{
		$(".not4ie").show();
		$(".only4ie").hide();
	}
});
var $epiq = (function ($) {

	var __i = 0;
	//  pt = 3/4 * px  ==> pt * 1.3 = px
	//var a4 = [595, 842]; 			// for a4 size paper width and height A4 at 72dpi!
	var a4 = [842*1.3 , 595*1.3]; 	// landscape!
	var a3 = [1191*1.3, 842*1.3];	// landscape & A3!
	var paper2use = a3;				// & format: 'a4' | format: 'a3'

	var rewidth = function(canvas, maxWidth)
	{
		var width = canvas.width;
		if( width <= maxWidth)
		{
			//return canvas;
		}

		var c 		= document.createElement('canvas');
		var wScale  = maxWidth / width;
		c.height 	= canvas.height * wScale;
		c.width 	= maxWidth;
		var cc 		= c.getContext('2d');
		cc.drawImage(canvas, 0, 0, canvas.width, canvas.height, 0, 0, c.width, c.height);

		//console.log("wScale:"+wScale+" -> "+canvas.height+" * "+wScale+" = "+c.height);
		//var win = window.open('', 'pdfpic');
		//win.document.write('<img src="'+c.toDataURL("image/png", 1.0)+'">');

		return c;
	}
	
	var splitImg = function(canvas/*HTMLCanvasElement*/, pageHeight/*:number*/) // : Array<CanvasRenderingContext2D>
    {
        var imgs = new Array();
        var imgHeight = canvas.height;
        var imgStart = 0;

        var dx = 0;
        var dy = 0;
        var dWidth = Math.min(canvas.width, paper2use[0]);
        var sx = 0;
        var sWidth = canvas.width;

        while(true)
        {
            var dHeight = pageHeight;
            var sy = imgStart;
			var sHeight = pageHeight;
			dHeight = sHeight;

            var c2 		= document.createElement('canvas');
            c2.height 	= dHeight;
            c2.width 	= dWidth;
			var slice 	= c2.getContext('2d');

            slice.drawImage(canvas, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight);
            imgs.push(slice);

			//console.log("sx:"+sx+" sy:"+sy+" sWidth:"+sWidth+" sHeight:"+sHeight+" dx:"+dx+" dy:"+dy+" dWidth:"+dWidth+" dHeight:"+dHeight);

			/*if(imgs.length == 1)
			{
				var img = c2.toDataURL("image/png");		//image/jpeg -> black background
				var win = window.open('', 'pdfpic');
				win.document.write('<img src="'+img+'">');
			}*/

            imgStart = sy + sHeight;

            if(imgStart >= canvas.height)
            {
                break;
            }
            if(imgs.length > 9)
            {
                console.log("ERR: TOO BIG PDF? ");
                break;
            }
        }
        return imgs;
	}
	
	var onpdfrendered = function(canvas, fn)
	{
		console.log('onpdf-step.2 canvas.width:'+canvas.width);
		//setTimeout for allowing the browser to repaint
		setTimeout(function() 
		{
			console.log('onpdf-step.3');
			canvas = rewidth(canvas, paper2use[0] - 40);
			//canvas.width = paper2use[0];
			//img.width = paper2use[0];
			//console.log('onpdf-step.4('+paper2use[0]+'):'+img.length);
			//var win = window.open('', 'pdfpic');
			//win.document.write('<img src="'+img+'">');
			//return;
			//TODO: make paper2use & resize & split img
			var doc = new jsPDF(
			{
				orientation: 'l',
				unit: 'pt',
				format: 'a3'
			});
			var hmax = paper2use[1] - 40;
			if(canvas.height > hmax)
			{
				var imgs/*:Array<CanvasRenderingContext2D>*/ = splitImg(canvas, hmax);
				for(var i=0;i<imgs.length;i++)
				{
					if(i > 0)doc.addPage();
					var w = Math.min(paper2use[0] - 40, imgs[i].canvas.width);
					var h = Math.min(paper2use[1] - 40, imgs[i].canvas.height);
					doc.addImage(imgs[i].canvas.toDataURL("image/png", 1.0), 'PNG', 20, 20);//, w, h);
				}
			}
			else
			{
				var img = canvas.toDataURL("image/png", 1.0);		//image/jpeg -> black background
				var w = Math.min(paper2use[0] - 40, canvas.width);
				var h = Math.min(paper2use[1] - 40, canvas.height);
				doc.addImage(img, 'PNG', 20, 20);//, w, h);
			}
			doc.save(fn);
			$("html, body").css("cursor", "default");
		}, 1);
	};
	
	var onpdf = function(ele, fn)
	{
        $("html, body").css("cursor", "progress");			//TODO: do we need more signs for 'please wait, currently working'?
		//, width:paper2use[0] if width is set, the rest is cut off
		html2canvas(ele, { onrendered: function(canvas){onpdfrendered(canvas, fn); }, scale:9 } );	//http://html2canvas.hertzen.com/configuration
		return false;
	};

	var showAlert = function(txt)
	{
		var tmpl = $('#alerttemplate');
		var a = tmpl.clone().show();
		$('#alerttxt', a).text(txt);
		a.appendTo(tmpl.parent());
		setTimeout(function(i, a) {
		
			if(i % 4 == 0)
			{
				a.toggle("slow", function(){ $(this).remove(); });
			}
			else if(i % 3 == 0)
			{
				a.toggle("explode", { pieces:9 }, "slow", function(){ $(this).remove(); });
			}
			else if(i % 2 == 0)
			{
				a.toggle("drop", { direction:"left" }, "slow", function(){ $(this).remove(); });
			}
			else
			{
				a.slideUp(999, function(){ $(this).remove(); });
			}

		}, 3999, __i++, a);
	};
	var copyCellBefore = function(btn)
	{
		var txt2copy = $.trim($(btn).closest("td").prev('td').text());
	    try
		{
		  var textarea = document.getElementById("cpytextarea");
		  textarea.value = txt2copy;
		  var a = $(document).scrollTop();	//actually, only needed for ie
		  textarea.select();
		  $(document).scrollTop(a);
		  var successful = document.execCommand('copy');
		  
		  if(!successful)
		  {
			showAlert('Oops, unable to copy');
		  }
		  else
		  {
			var txt2show = txt2copy.length > 33 ? txt2copy.substring(0, 33)+"..." : txt2copy;
			showAlert('Copied '+txt2copy.length+' characters:\n{'+txt2show+'}');
		  }
		  
		  return false;
		}
		catch (err)
		{
		  showAlert('Oops, unable to copy: '+err);
		  return false;
		} 
	};

	var oncsv = function(fileDownload)
	{
		var sRecordSeparator  = "\r\n";
		var sCellSeparator    = ";";
			
		var sCSV = '';
		var iCSV = 0;
		$("a").each(function(index)
		{
			var a = $(this);
			var href = a.attr('href');
			if(!href || (href.indexOf('#') == 0) || (href.indexOf('data:') == 0)) return;
			var title = a.attr('title');
			//href = index;
			//sCSV += ""+title+""+sCellSeparator+""+href+""+sRecordSeparator;
			sCSV += (++iCSV)+sCellSeparator+href+""+sRecordSeparator;
		});

		var ie = (window.navigator.msSaveOrOpenBlob != undefined); 
		var dobtoa = false;	
		if (dobtoa)
		{
			sCSV = btoa(sCSV);          //btoa doesn't support \uFEFF
		}
		else
		{
			if(!ie)sCSV = encodeURIComponent(sCSV);
			sCSV = '\uFEFF'+sCSV;       //magic for excel
		}
	
		{ //offer for open/download
			var mimetype = "text/csv";//"vnd.openxmlformats-officedocument.spreadsheetml.sheet";//"application/vnd.ms-excel";//"text/comma-separated-values"
			var enc = dobtoa ? ";base64" : "";
			var url = "data:"+mimetype+';charset=utf-8'+enc+','+sCSV;
	
		  fileDownload.href = url;

		  if(ie)
		  {				//possible solution: downloadify(http://pixelgraphics.us/downloadify/test.html , requires flash)
			var blob = new Blob([sCSV], { type: 'text/csv;charset=utf-8;' });
			var url2 = window.URL.createObjectURL(blob);
			fileDownload.href = url2;
			window.navigator.msSaveOrOpenBlob(blob, "epiq-links.csv");
		  }
		  else
		  {
			fileDownload.click();
		  }
		}	
	};
	
	return {
		copyCellBefore : copyCellBefore,
		showAlert : showAlert,
		onpdf : onpdf,
		oncsv : oncsv
	};

})(jQuery);	//iife
