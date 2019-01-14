# Angular SSR / Universal

## create Ng2+ project
	with the CLI, as usual

## Use Angular Console to convert to Universal project.
	Changed / New files:
	angular.json - new builder for ssr build
	package.json - new angular packages
	main.ts
	tsconfig.server.json (new file)
	app.server.module.ts
	main.server.ts
### Angular Console:
<img src="ng.ssr.ng.console.png" width="550px">
### Angular Console generates SSR code:
<img src="ng.ssr.ng.console.ssr.generation.png" width="550px">

## install server-side support:
	$ npm i @nguniversal/express-engine --save
	$ npm i @nguniversal/module-map-ngfactory-loader --save	# lazy loading support
	$ npm i ts-loader --save-dev
	$ npm i node-fetch --save
	$ npm i compression --save

## implement server (example: https://github.com/kalyan11021980/angular-ssr-starter)
### webpack.server.config.js (with tsc (ts2js), ts-loader)
### server.ts with
	ngExpressEngine				# from @nguniversal/express-engine
	AppServerModuleNgFactory		# from ./dist/sesrver/main	created by the ng-ssr build
	provideModuleMap			# from @nguniversal/module-map-ngfactory-loader
	domino						# 'window' support on the server side
	compression					# use: app.use(compression());
	
### server.ts:
<img src="ng.ssr.express.png" width="550px">
### server.ts:
<img src="ng.ssr.express.server.ts.png" width="550px">
### Client side determinates if SSR rendered:
<img src="ng.ssr.isPlatformServer.png" width="550px">
	
### package.json: add new build type:
	"serve:ssr":"node dist/server.js"
	"webpack:server":"webpack --config webpack.server.config.js --progress --colors"
	"build:client-and-server-bundles":"ng build --prod && ng run ssr:server:production"	# 'ssr' is the project name (projects/ssr) in angular.js
	"bulid:ssr":npm run build:client-and-server-bundles && npm run webpack:server
	"start-ssr":"npm run build:ssr && npm run serve:ssr"

### build & run:
	$ npm run start-ssr

## CI/CD with Jenkins
### Build
1. Create a Freestyle project
2. set Build Triggers (eg. poll SCM or GitHub hook trigger)
	1. you possibly need to add webhook in github, set git repo URL (git@github.com:???.git)
3. Build -> Execute Shell -> Command:
```sh
npm install
npm run build:ssr
pm2 restart all
```
4. [Apply]

### Pipeline
1. Create a Pipeline
2. General: set 'Do not allow concurrent builds'
3. set Build Triggers: Poll SCM; Schedule: H/5* * * *	//poll every 5 mins
4. set Pipeline Definition 'Pipeline script from SCM'
	1. SCM Git, set git repo URL (git@github.com:???.git), set Branch
	2. Script path: Jenkinsfile, content is in git:
```js
node {
	stage('checkout scm') {
		git branch: 'master', url: 'git@github.com:myusername/myprojectname.git'
	}
	stage('install node modules') {
		sh "npm install"
	}
	stage('build') {
		sh "npm run build:ssr"
	}
	stage('deploy') {
		sh "pm2 restart all"
	}
}
```
5. [Apply]
