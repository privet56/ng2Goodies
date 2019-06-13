set "PATH=%~dp0..\apache-maven\bin;%PATH%"
set "PATH=%~dp0..\jdk\bin;%PATH%"
set "JAVA_HOME=%~dp0..\jdk"

mvn clean install
