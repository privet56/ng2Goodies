rem -------- SETUP LOCAL NODEJS - START ---------
rem %NODE_DIR%\node_modules\npm\etc\npmrc
rem 	and
rem %NODE_DIR%\node_modules\npm\npmrc
rem 	should have the content:
rem prefix=${NODE_DIR}\node_modules\npm
rem cache=${NODE_DIR}\npm-cache
rem 
rem then install:
rem 
rem npm install -g npm@latest -f
rem npm install -g angular-cli
rem npm install -g outdated
rem npm install -g npm-check-updates
rem npm install -g node-sass
rem npm rebuild node-sass						//execute this step also for your project!
rem -------- SETUP LOCAL NODEJS - END ---------

cls

set "PATH=%~dp0..\devenv\git;%~dp0..\devenv\git\bin;%PATH%"
set "PATH=%~dp0..\devenv\nodejs;%~dp0..\devenv\nodejs\node_modules\npm;%PATH%"

set APPDATA=%~dp0../devenv/MsVSCode
set USERPROFILE=%~dp0../devenv/MsVSCode

start "" %~dp0../devenv/MsVSCode/Code.exe %~dp0
start "" cmd /c "timeout 9 & start http://localhost:4200/"
ng serve
