# TypeScript & Angular 2 Goodies:

## PersistentRouterOutlet.ts for ng2 (Angular 2 version 2.2.3)
	(allows to switch between routes without reloading already loaded routes)
	use this way:
	@NgModule({
	...
	providers: [
		{provide: RouterOutlet, useClass: PersistentRouterOutlet }
	]
	})
	export class MyRoutingModule
	{
		...


## sani.ts: SanitizerPipe
	(allows inserting HTML into the DOM)
	
## truncate.ts: TruncatePipe
	{{ value | truncate:99 }}

## uHtmlUtil.ts
	(handeles recursive string-replacement in arbitrary objects and allows the generation of XML objects)
	
## ValueEmitter.ts
	(unites value holder variable with EventEmitter)

## startNgProject.bat
	starts all necessary apps for ng2 development: node, vscode, browser and 'ng serve'
	necessary directory structure:
	-- devenv
	---- git
	---- MsVSCode
	---- nodejs
	-- [yourapp]

## soap/*
	supports accessing XML SOAP WebServices from Angular 2 apps
	and
	maps the response to native TypeScript objects
	(based on https://github.com/autopulous/angular2-soap)

## LINQ Extension
	Do you need to use a linq-based environment to call a stored procedure with unknown/unpredictable return structures?
	You can use linq/LinqExtensions.cs
	(as a simple 'dynamic' keyword does not lead to the expected result)
	
	Example:

	public string getProcReturnAttribute(DataContext dataContext, string sAttrName)
	{
		string query = "EXEC [dbo].[SPO_GetData] {0}, {1}, {2}";
		query = string.Format(query, “name”, anEmail == null ? "NULL" : "'" + anEmail + "'", anID);
		var datas = LinqExtensions.ExecuteQuery(dataContext, query);
		foreach(var data in datas)
		{
			//data.getAllAttrs();
			string sAttrVal = data.getAttr(sAttrName);
			if(ILikeThisAttrVal(sAttrVal))
				return sAttrVal;
		}
		return null;
	}

## Docker
	A short presentation & introduction to its application in practice.
	docker/docker.pptx

## Outlook Email Sender
	MFC Visual Studio project to send Email through Outlook (COM)
	outlookEmailSender/sender.vcproj

## NAGIOS check implementation in Perl:
	nagios_dyn_check_http.pl
	Perl script to be called by NAGIOS to check if the HTTP connection is alive
	nagios_dyn_check_http/check_http.pl

## Server Landscape Visualization
	Create a dynamic server landscape visualization with data flow, graphs and plots 
	Used technologies:
	jQuery, AngularJS, jqPlot, Raphaël ( https://en.wikipedia.org/wiki/Rapha%C3%ABl_(JavaScript_library) )
