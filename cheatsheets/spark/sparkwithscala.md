# Spark 2 with Scala
**Suggested Prerequisites**:
1. JDK, Scala(>=version 2.11.12), IntelliJ(with scala & sbt(>=version 0.13.17) plugin), sbt, spark binaries
2. winutils.exe(64bit, on windows, in c:/hadoop/bin/, set system env var HADOOP_HOME=c:\hadoop + add to PATH c:/hadoop/bin)
3. you need SPARK_HOME & PATH += %SPARK_HOME%\bin
3. example data: https://github.com/dgadiraju/data

### Scala Project:
```scala
package my
import org.apache.spark.{SparkConf, SparkContext}
object M {
    def main(arg: Array[String]): Unit = {
        val conf = new SparkOnf().setMaster(args(0)).setAppName("my")
        var sc = new SparkContext(conf)
        sc.setLotLevel("ERROR")
        val orderItems = sc.textFile(args(1))
        val revenuePerOrder = orderItems
                .map(oi => (oi.split(",")(1).toInt, oi.split(",")(4).toFloat))
                .reduceByKey( + )
                .map(oi => oi._1 + "," + oi._2)
        revenuePerOrder.saveAsTextFile(args(2))
    }
    def nCr(n: Int, r: Int) = {
        def fact(i: Int) = {
            var res = 1
            for(e <- i to 1 by -1)
                res = res * e
            res
        }
        fact(n)/(fact(n-r) * fact(r))
    }
}
```
sbt/spark commands:
```sh
sbt package # creates my.jar
sbt run
sbt "run-main M cmdargument"

spark-shell
scala> sc  # available out-of-the-box within the spark-shell
spark-submit --class my.M my.jar local input\data output\data
```
build.sbt
```scala
name := "myapp"
version := "0.1"
scalaVersion := "2.11.12"
libaryDependencies += "org.apache.spark" %% "spark-core" % "2.3.0"
```
#### project structure:
    ./build.sbt
    ./src/
    ./target/

