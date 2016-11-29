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

