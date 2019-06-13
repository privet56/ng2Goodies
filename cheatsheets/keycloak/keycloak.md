# keycloak

keycloak is a wildfly-based auth server.

## Realm
Set up a realm for your app, in the keycloak admin console 

## docu:
1. download jdk8+ & Maven
1. set PATH & JAVA_HOME
    1. set "PATH=%~dp0..\apache-maven\bin;%PATH%"
    1. set "PATH=%~dp0..\jdk\bin;%PATH%"
    1. set "JAVA_HOME=%~dp0..\jdk"
1. > $ git clone -c core.symlinks=true https://github.com/keycloak/keycloak-documentation.git
1. > $ mvn clean install
1. result: /target/index.html.
1. convert with calibre into pdf...
