<link rel="stylesheet" href="_github-markdown.css">

# Cheatsheets:

#### [Angular Server Side Rendering](ngssr/ng.ssr.md)
#### [Angular / Rx](../../../../artiFlow/blob/master/README.md#rx-cheatsheet)

#### [Azure](azure/azure.md)
#### [Google Cloud Platform](gcp/gcp.md)

#### [SmartGWT](gwt/smartgwt.md)

#### [Docker (PowerPoint Presentation, 2017)](./../docker/docker.pptx)
#### [Docker for Windows](./../docker/docker4windows.md)
#### [Kubernetes](./../docker/k8s.md)
#### [CI/CD with Jenkins and Kubernetes](ci_cd_jenkins_kubernetes.md)
#### [Kubernetes on AWS](./../docker/k8s.on.aws.md)
#### [Local Kubernetes Environments with minikube](./../docker/k8slocal.md)
#### [Security in Kubernetes Environment](sectest/sec_k8s.md)
#### [Helm - basics](helm/helm.md)
#### [Helm - advanced (mentioning istio too)](helm/helm4k8s.md)
#### [Istio](helm/istio.md) & [Istio-CodeFresh](helm/istio_helm_canary.md)
#### [Multicloud with k8s & Istio & Spinnaker](helm/multicloud.md)
#### [k8s & Rancher](devops/rancher.md)
#### [Spinnaker](devops/spinnaker.md)

#### [Kafka](./kafka/kafka.md)

#### [MS Dynamics CRM](./ms_dynamics/ms_dynamics.md)

### PHP
#### [PHP - HHVM, Hacklang, PHP-FPM](hhvm/hhvm.md)
#### [PHP - Advanced Laravel](php/laravel.md)
#### [PHP - RxPHP](php/rxphp.md)

#### [Python / Django](../../../../spycy/blob/master/cheatsheet/django.md)
#### [Python / Flask](../../../../spycy/blob/master/cheatsheet/flask.md)

### Qt
#### [Qt .pro/QML](../../../../qBoss/blob/master/qt_cheatsheet.md)
#### [Qt For Android Gotchas (PDF)](../../../../qBoss/blob/master/qt4android_hints/qt4android_hints_for_beginners.pdf)
#### [QtWS18](qt/qtws18.md)

### Security
#### [Penetration Tests](./sectest/pentest.md)
#### [Security Testing](./sectest/sectest.md)
#### [OAuth / OpenID / JWT](./sectest/oauth.md)

#### [Solr](./solr/solr.md)

#### [RxJava](./rx/rxjava.md)
#### [RxJava & ReactiveJ](./rx/reactivej.md)

#### [Scrum / Kanban / SAFe](scrum/scrum.md)

#### [Spark](spark/spark.md)
#### [Spark with PySpark](spark/spark_pyspark.md)
#### [Spark with Scala](spark/sparkwithscala.md)

#### [Interpersonal Skills](interpersonalskills.md)

#### [Yocto](yocto/yocto.md)
#### [ZooKeeper](zookeeper/zookeeper.md)
#### [Hazelcast](./hazelcast/hazelcast.md)
#### [Redis](./redis/redis.md)
#### [Vert.x](./vertx/vertx.md)

### DevOps
#### [GitLab](./devops/gitlab.md)
#### [Varnish](./devops/varnish.md)
#### [PostgreSQL](./devops/postgres.md)

.

## Diverse:

.

#### How to protect Secret Keys in JavaScript source code?
use jscrambler
1. use jscrambler, with config entry "propertyKeysObfuscation"
2. **Take care**: this hint is not hacker-safe, but often ~good-enough!
3. cfg prop: "name": "propertyKeysObfuscation"
```sh
npm install jscrambler --save-dev 
npm i --save-dev jscrambler-webpack-plugin 
```

#### How to convert PSD to HTML/CSS & pics ?
Use Avocode (desktop app, available for macOS, Win, Linux)
1. Use Avocode (the app is not free) (can also handle Sketch designs with a plugin)
2. After opening the project, you can edit the CSS styles.
3. can export images
4. often, you edit the HTML manually and use the styles & images given by Avocode
5. app shows padding & margin of elements visually

#### How to do (mobile) Cross-Browser testing? 
Use online service of http://www.browserstack.com (not free!)
1. Can do:
    1. live: interactive test & debug of websites in real browsers & mobile devices
    2. Automate
    3. Screenshots & Responsive
2. you can choose from a lot of browser-versions & OSs(Win, macOS, iOS, Android)
3. Plugin for Chrome: 'Local Testing' for non-public websites, eg. from localhost

#### How to speed up Apache?
Use mod_pagespeed: it compresses JS & CSS
```sh
wget https://dl-ssl-google.com/dl/linux/direct/mod-pagespeed-stable_current_amd64.deb
dpkg -i mod-pagespeed*.deb
sudo service apache2 restart
gedit /etc/apache2/mods-available/pagespeed.conf # -> ModPagespeed on|off
gedit /etc/apache2/mods-enabled/pagespeed.conf   # -> /pagespeed_admin = Admin Area!
sudo service apache2 reload
```
/etc/apache2/mods-available/pagespeed.conf
```xml
<IfModule pagespeed_module>
    ModPagespeed on
    ...
```
/etc/apache2/mods-enabled/pagespeed.conf
```xml
<Location /pagespeed_admin>
    Order allow,deny
    Allow from localhost
    Allow from 127.0.0.1
    Allow from 0.0.0.0
    SetHandler pagespeed_admin
</Location>
<Location /pagespeed_global_admin>
    Order allow,deny
    Allow from localhost
    Allow from 127.0.0.1
    Allow from 0.0.0.0
    SetHandler pagespeed_global_admin
</Location>
    ModPagespeedStatisticsLogging on
```
