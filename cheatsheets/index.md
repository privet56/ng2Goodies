# Cheatsheets:
#### [Azure](azure.md)
#### [Helm - basics](helm.md)
#### [Helm - advanced](helm4k8s.md)
#### [Angular Server Side Rendering](ng.ssr.md)
#### [Penetration Tests](pentest.md)
#### [Scrum](scrum.md)
#### [Spark](spark.md)
#### [Spark with PySpark](spark_pyspark.md)

### Diverse:

#### How to protect Secret Keys in JavaScript source code?
    use jscrambler, with config entry "propertyKeysObfuscation" :
    install:
```sh
    npm install jscrambler --save-dev 
    npm i --save-dev jscrambler-webpack-plugin 

    cfg prop: "name": "propertyKeysObfuscation"
```
Disclaimer: this hint is not hacker-safe, but often ~good-enough!
