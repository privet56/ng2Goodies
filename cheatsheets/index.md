<link rel="stylesheet" href="_github-markdown.css">

# Cheatsheets:

#### [Azure](azure/azure.md)
#### [Docker (PowerPoint Presentation, 2017)](./../docker/docker.pptx)
#### [Docker for Windows](./../docker/docker4windows.md)
#### [Kubernetes](./../docker/k8s.md)
#### [CI/CD with Jenkins and Kubernetes](ci_cd_jenkins_kubernetes.md)
#### [Helm - basics](helm/helm.md)
#### [Helm - advanced (mentioning istio too)](helm/helm4k8s.md)
#### [Angular Server Side Rendering](ngssr/ng.ssr.md)
#### [Angular / Rx](../../../../artiFlow/blob/master/README.md#rx-cheatsheet)
#### [Python / Django](../../../../spycy/blob/master/cheatsheet/django.md)
#### [Python / Flask](../../../../spycy/blob/master/cheatsheet/flask.md)
#### [Qt .pro/QML](../../../../qBoss/blob/master/qt_cheatsheet.md)
#### [Qt For Android Gotchas (PDF)](../../../../qBoss/blob/master/qt4android_hints/qt4android_hints_for_beginners.pdf)
#### [Penetration Tests](pentest.md)
#### [Scrum](scrum/scrum.md)
#### [Spark](spark/spark.md)
#### [Spark with PySpark](spark/spark_pyspark.md)
#### [Interpersonal Skills](interpersonalskills.md)
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
