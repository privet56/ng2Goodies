de.sc.portal.env.dlg = {};

de.sc.portal.env.dlg.makedglopts = function(forpackage, opts)
{
	var dialogOpts =
    {
        autoOpen: false,
        //modal: true,	//does it have problems with min/max ?
        /*show:
        {
			effect: "fade",
			duration: 500
		},
		/ *hide: document.all ? null : 
		{
			effect: "explode",
			duration: 500
		},*/
        position: "center",
        draggable: true,
        resizable: true,
        minWidth:720,
        height:520,
        minimize:false,
        maximize:true,
        maximizable: true,
        closable: true,
        icons: { "maximize" : "ui-icon-arrow-4-diag" },
        
		buttons:
		{
			'Close':function(){$(this).dialog('close');}
		},
		beforeMaximize: function(){},
		'open':  forpackage.onDlgOpen,
		'load':  forpackage.onDlgOpen,
		'close': forpackage.onDlgClose,
		'resize':forpackage.onDlgResize
    };
    
    if(opts)
    	dialogOpts = $.extend(dialogOpts, opts);
    				
	return dialogOpts;
};