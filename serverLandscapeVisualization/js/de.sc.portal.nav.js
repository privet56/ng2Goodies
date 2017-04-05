de.sc.portal.nav = {};

de.sc.portal.nav.onReady = function($log, title)  
{
	$("#navi").button({ icons: {primary:'', secondary:'ui-icon-triangle-1-s'}});
	
	$("#appTitleTest").hide();	//PROD, also on 8080
	$("#smoenvlink").html("&nbsp; &nbsp; &nbsp; &nbsp; ");
	
	var blurTimer = null;
	$("#navi_menu").menu(
	{
		_closeOnDocumentClick: function(event){return true;},
		select: function(event, ui)
		{
	            $("#navi_menu").hide();
	            $("#navi").button("option", {icons: { secondary: "ui-icon-triangle-1-" + ($("#navi_menu").is(':visible') ? 'n' : 's') }});
	            self.location.href = $("a", ui.item).attr("href");
		},
		blur: function()
		{
			blurTimer = setTimeout(function()
			{
	            $("#navi_menu").hide();
	            $("#navi").button("option", {icons: { secondary: "ui-icon-triangle-1-" + ($("#navi_menu").is(':visible') ? 'n' : 's') }});
			},
			900);
		},
		focus: function()
		{
			clearTimeout(blurTimer);
		}
	});
	
	if(document.all && title)	//very very bad hack for ie8+angular
	{
		if (document.title.indexOf("{{") > -1)
			document.title = title;
	}
};
de.sc.portal.nav.onNaviButton = function()
{
	$("#navi_menu").toggle();
	$("#navi").button("option", {icons: { secondary: "ui-icon-triangle-1-" + ($("#navi_menu").is(':visible') ? 'n' : 's') }});
};
