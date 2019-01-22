<link rel="stylesheet" href="_github-markdown.css">

# Cheatsheets:

#### [Angular Server Side Rendering](ngssr/ng.ssr.md)
#### [Angular / Rx](../../../../artiFlow/blob/master/README.md#rx-cheatsheet)

#### [Azure](azure/azure.md)
#### [Google Cloud Platform](gcp/gcp.md)

#### [Docker (PowerPoint Presentation, 2017)](./../docker/docker.pptx)
#### [Docker for Windows](./../docker/docker4windows.md)
#### [Kubernetes](./../docker/k8s.md)
#### [CI/CD with Jenkins and Kubernetes](ci_cd_jenkins_kubernetes.md)
#### [Local Kubernetes Environments with minikube](./../docker/k8slocal.md)
#### [Helm - basics](helm/helm.md)
#### [Helm - advanced (mentioning istio too)](helm/helm4k8s.md)
#### [Istio](helm/istio.md)

#### [Kafka](./kafka/kafka.md)

#### [MS Dynamics CRM](./ms_dynamics/ms_dynamics.md)

#### [PHP - HHVM, Hacklang, PHP-FPM](hhvm/hhvm.md)
#### [PHP - Advanced Laravel](php/laravel.md)
#### [PHP - RxPHP](php/rxphp.md)

#### [Python / Django](../../../../spycy/blob/master/cheatsheet/django.md)
#### [Python / Flask](../../../../spycy/blob/master/cheatsheet/flask.md)

#### [Qt .pro/QML](../../../../qBoss/blob/master/qt_cheatsheet.md)
#### [Qt For Android Gotchas (PDF)](../../../../qBoss/blob/master/qt4android_hints/qt4android_hints_for_beginners.pdf)

#### [Penetration Tests](./sectest/pentest.md)
#### [Security Testing](./sectest/sectest.md)

#### [Solr](./solr/solr.md)

#### [RxJava](./rx/rxjava.md)
#### [RxJava & ReactiveJ](./rx/reactivej.md)

#### [Scrum / Kanban](scrum/scrum.md)

#### [Spark](spark/spark.md)
#### [Spark with PySpark](spark/spark_pyspark.md)
#### [Spark with Scala](spark/sparkwithscala.md)

#### [Interpersonal Skills](interpersonalskills.md)

#### [Yocto](yocto/yocto.md)
#### [ZooKeeper](zookeeper/zookeeper.md)
#### [Hazelcast](./hazelcast/hazelcast.md)
#### [Redis](./redis/redis.md)
#### [Vert.x](./vertx/vertx.md)
.

### Diverse:

.

#### How to protect Secret Keys in JavaScript source code?
    use jscrambler, with config entry "propertyKeysObfuscation" :
    install:
```sh
npm install jscrambler --save-dev 
npm i --save-dev jscrambler-webpack-plugin 

cfg prop: "name": "propertyKeysObfuscation"
```
    Disclaimer: this hint is not hacker-safe, but often ~good-enough!

