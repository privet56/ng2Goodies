de.sc.portal.env.dlg.r = {};

de.sc.portal.env.dlg.r.dlg_height_original = 0;
de.sc.portal.env.dlg.r.div_height_original = 0;
de.sc.portal.env.dlg.r.tbl = 0;

de.sc.portal.env.dlg.r.onDlgOpen = function()
{
	de.sc.portal.env.dlg.r.dlg_height_original = $(this).css('height').replace(/px/, '');
	de.sc.portal.env.dlg.r.div_height_original = $("#dlg_reachability_list", $(this)).css('height').replace(/px/, '');
};
de.sc.portal.env.dlg.r.onDlgClose = function()
{
  
};
de.sc.portal.env.dlg.r.onDlgResize = function()
{
	var dlg   = $(this);
	var dlg_h = dlg.css('height').replace(/px/,'');
	//500	->	300
	//dlg_h -> div_h
	var div_h = (dlg_h * de.sc.portal.env.dlg.r.div_height_original) / de.sc.portal.env.dlg.r.dlg_height_original;
	$('#dlg_reachability_list', dlg).css('height', div_h);
};
de.sc.portal.env.dlg.r.checkavailability = function(button)
{
	$("#dlg_reachability").dialog('open');
	
	var div = $("#dlg_reachability_list");
	{
		$("input[type=search]", $("#dlg_reachability")).each(function(index){$(this).val('');});
		de.sc.portal.env.dlg.r.tbl.search('');
		de.sc.portal.env.dlg.r.tbl.clear().draw();
	}
	
	$("#dlg_reachability_wait").show();
	
	var lnks = new Array();
	
	var myurlWithoutAnchor = de.sc.portal.env.dlg.r.getUrlWithoutAnchorAndParams(window.location.href);
	
	$("a[href!='#']", $("#cluster8080, #cluster9080")).each(function(index)	//ca. 80 hrefs
	{
		var href = $(this).attr("href");
		if (href.indexOf("http") !== 0)return;
		if (href.indexOf("://monitoring.global-intra.net/") > -1)return;	//don't check nagios
		
		var hrefWithoutAnchor = de.sc.portal.env.dlg.r.getUrlWithoutAnchorAndParams(href);
		if (hrefWithoutAnchor == myurlWithoutAnchor)return;
		
		if(de.sc.isempty(hrefWithoutAnchor))return;
		
		lnks.addIfNotIn(hrefWithoutAnchor);
	});
	
	$("#dlg_reachability_sum").html("0 / "+lnks.length);
	
	for(var i=0;i<lnks.length;i++)
	{
		var href = lnks[i];
		de.sc.portal.env.dlg.r.checkavailability4lnk(href, lnks, div, de.sc.portal.env.dlg.r.tbl);
	}
};
de.sc.portal.env.dlg.r.checkavailability4lnk = function(href, lnks, div, tbl)
{
	$.ajax
	({
		url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+href) : "_Mod_cluster Status.htm"),
		dataType:"html"
	})
	.success(function(data)
	{
		var bok = !de.sc.isempty(data);
		var entries_now = tbl.data().length;
		if((entries_now == 55) && (window.location.href.indexOf("http") !== 0))bok = false;	//dummy failure
		$("#dlg_reachability_sum").html((entries_now+1)+" / "+lnks.length);
		
		tbl.row.add([
			""+(entries_now + 1),
			((bok === true) ? ' ' : '!') + "OK <img src='"+((bok === true) ? './img/check_ok.png' : './img/check_notok.png')+"' data-ok='"+bok+"' />",
			"<a href='"+href+"' target='_new' class='"+((bok === true) ? 'check_ok' : "check_notok\' style='color:red;")+"'>"+href+"</a>"
        ]).draw();
		
		if(entries_now >= (lnks.length-1))
		{
			$("#dlg_reachability_wait").toggle("drop", { direction:"right" }, 2222 );
		}
	})
	.error(function(xhr, statusmsg, err)
	{
		de.sc.log("\ncheckavailability:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+href+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
	});
};
de.sc.portal.env.dlg.r.getUrlWithoutAnchorAndParams = function(url)
{
	if(de.sc.isempty(url))return url;
	if(url.indexOf('?') > -1)url = url.substr(0, url.indexOf('?'));
	if(url.indexOf('#') > -1)url = url.substr(0, url.indexOf('#'));
	return url;	
};
