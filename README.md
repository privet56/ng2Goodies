# TypeScript, Perl, JS, C# & Angular 2+ Goodies:

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
	(see comments for setting the necessary content of npmrc)
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

## .NET C# Lib: net_csharp_lib/*.cs
	with LDAP helper, table column helper, Excel support, Templater, Logging, Utils, and
	LINQ Extension:
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
	
![docker.png](https://raw.githubusercontent.com/privet56/ng2Goodies/master/docker/docker.png)

### Oracle Database running on Docker For Windows:

![docker4OracleOnWindows.png](https://raw.githubusercontent.com/privet56/ng2Goodies/master/docker/docker4OracleOnWindows.png)

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
	
![environment.overview.with.raphael.png](https://raw.githubusercontent.com/privet56/ng2Goodies/master/serverLandscapeVisualization/img/environment.overview.with.raphael.png)
![render.times.ff.ie8.diff.png](https://raw.githubusercontent.com/privet56/ng2Goodies/master/serverLandscapeVisualization/img/render.times.ff.ie8.diff.png)

### With Dynamic Documentation: client side Screenshot-, PDF- and CSV- generation and also 3D Button.

![3dbutton.gif](https://raw.githubusercontent.com/privet56/ng2Goodies/master/serverLandscapeVisualization/dynadocu/3dbutton.gif)

## Win Manager
	MFC Visual Studio project
	
![wins.png](https://raw.githubusercontent.com/privet56/ng2Goodies/master/wins/Release/wins.png)

## PL Lib
	Perl library with project independent useful functions
	(e.g. cfg, logging, trim, ...)
	pllib/pllib.pl

## SQL Lib
	Oracle DB search all Tables
	Procedure with Bulk and Cursor operation
	sql/*.sql
	
## iOS: objC Lib
	Objective C Library with project independent useful functions
	(e.g. XML parser, HTML parser, ZIP, ...)
	iIOS_objc_lib/*

## C++ Lib
	HTML parser, Progress-Dialog,
	OLE Automation to convert HTML to RTF with Word (COM)
	Example:
	void ConverttoRTF()
	{
		COLEWordAutomation _word;
		if(FAILED(_word.m_hr))
			return;

		_word.OpenDocument(m_sInputFile);

		//while(_word.Search("^g"))_word.Delete();	//don't remove pics!!!

		CString sExt = ".rtf";
		int iSaveAsType = RTF;

		{	//DOC begin
			CString soutputfile(m_sOutputFile+":");soutputfile.MakeLower();
			if(soutputfile.Find(".doc:") > 1)
			{
				sExt = ".doc";
				iSaveAsType = DOC;

				{
					CComPtr<IDispatch> pDispDocs;
					pDispDocs.Attach(_word.m_pDispActiveDoc);
					_word.EmbedPictures(pDispDocs);
					pDispDocs.Detach();
				}
				_word.SaveAs(m_sOutputFile, iSaveAsType);
				_word.CloseDocument();
				_word.CloseWord();
				return;
			}
		}	//DOC end

		_word.SaveAs(m_sOutputFile+sExt, iSaveAsType);
		_word.CloseDocument();
		_word.OpenDocument(m_sOutputFile+sExt);

		{
			CComPtr<IDispatch> pDispDocs;
			pDispDocs.Attach(_word.m_pDispActiveDoc);
			_word.EmbedPictures(pDispDocs);
			pDispDocs.Detach();
		}
		_word.SaveAs(m_sOutputFile, iSaveAsType);
		_word.CloseDocument();
		::DeleteFile(m_sOutputFile+sExt);

		_word.CloseWord();
	}

