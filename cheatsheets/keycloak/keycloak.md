<link rel="stylesheet" href="../_github-markdown.css">

# keycloak

1. keycloak is a wildfly-based open-source auth server.
1. supported protocols: openID(preferred), saml2, kerberos
1. can use user federation (into ldap or active directory)
1. can SSO (Single Sign On, within a realm) (works for Web, Mobile and Desktop Apps)
1. can OTP (one-time-password)
1. with OpenID Connect, uses OAuth 2.0 tokens
1. with OpenID Connect, uses JWT token, with payload (with roles), after login
    * your app can verify, with the help of the public key of the keycloak-server, if the token is valid
    * verify by
        * check the signature with Realm Public Key , or
        * check via HTTP Post to keycloaks /token_introspection/endpoint
    * Token Types:
        * **Access**    Token (short lived (minutes)) for accessing resources
        * **Refresh**   Token (long lived (days)) for requesting new tokens
        * **Offline**   Token (almost never expires)
        * **ID**        Token (contains info about user (openid connect))

1. "client" = an app, to be secured, using keycloak

## Realm
Set up a realm for your app, in the keycloak admin console 

## Docu: https://www.keycloak.org/docs/3.2/index.html
1. download jdk8+ & Maven
1. set PATH & JAVA_HOME
    * set "PATH=%~dp0..\apache-maven\bin;%PATH%"
    * set "PATH=%~dp0..\jdk\bin;%PATH%"
    * set "JAVA_HOME=%~dp0..\jdk"
1. > $ git clone -c core.symlinks=true https://github.com/keycloak/keycloak-documentation.git
1. > $ mvn clean install
1. result: /target/index.html.
1. convert with calibre into pdf...

## Theming:
1. copy existing %KEYCLOAK_INSTALL_DIR%\themes\keycloak\ (only the subdirs you need! (account/admin/common/email/login/welcome))
2. adjust & style the freemarker templates (*.ftl)
3. build a .jar -> deploy into the keycloak-wildfly!

## Adapter
1. Adapter = lib allowing to communicate from your app to keycloak
1. there are adapters for nodejs, apache(mod_auth_oidc), angular, tomcat, spring(-boot: keycloak-spring-boot-starter), etc...

## TODO:
1. how to get & use offline Token ?
