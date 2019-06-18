@ECHO OFF
ECHO Starting PHP FastCGI...
set PATH=%~dp0.\php;%PATH%
%~dp0.\php\php-cgi.exe -b 127.0.0.1:9123
