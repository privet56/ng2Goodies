# Apache Spark
	Spark = a scala app (https://github.com/apache/spark/), with APIs in java, scala, python, r
		= distributed high performance computation engine
		= a lot faster than the traditional MapReduce of Hadoop, because in-memory as far as possible
		= has a Spark UI (web)
	Spark = Spark-SQL & Streaming & MLlib & GraphX
	https://spark-packages.org/	 = 3rd party libs
## Terms
	RDD = Resilient Distributed Dataset
		is Immutable in memory object
		is lazy & type-safe
		has partitions. more partitions -> more parallelism
	DataFrame = RDD with Schema and Optimizer
		but we lost type-safety in comparison with RDD
		cannot lambdas
	DataSet = type-safe AND has Optimizer AND can lambdas!
		(available from Spark v. 1.6)
	DAG = Directed Acyclic Graph
		= A flow control of RDDs through Transformations from Source, ending with Actions
	Transformations = change an RDD 
		e.g Map, ReduceByKey, GroupByKey, JoinByKey, SparkSQL
	Actions = lazy loaded process will be started after defining all the planned actions
		eg. Count, Take, Foreach
	DataBricks Notebook = Web based UI
	MLlib can classification, max,min,variance,correlation(eg. pearson), random forest
### Distributed Data Source is recommended, like
	hdfs/yarn
	s3
	dbfs
	hive (Spark-SQL can read hive!)
	Hadoop Input Format (eg. MongoDB, RDBMS, HBase, Neo4J, Cassandra)
## Components
	Driver Program = SparkShell or your app
		has SparkContext
	Cluster Manager coordinates the Worker Nodes
		(default from Spark or yarn)
	Worder Node with Executor and Cache and Tasks
## Flume Java
	Approach, where I write code like single-threaded, but executed on the cluster behind the scenes
### Word Count in Scala & Spark
	val conf = new SparkConf().setMaster("local[2]")
	val sc = new SparkContext(conf)
	val lines = sc.textFile(path, 2)			# Transformation, executed in the Driver
	val words = lines.flatMap(_.split(" "))		# Transformation (split executed on workers)
	val pairs = words.map(word => (word, 1))	# behind the scenes, RDDs are used (map executed on workers)
	val wordCounts = pairs.reduceBykey(_ + _)
	val localValues = wordCounts.take(100)		# here is the code executed on the cluster!
	localValues.foreach(r => println(r))
### Shell
	./spark-shell --master local[1]		# allocate just 1 thread, this is a scala shell, context is available as sc, session as spark
	> val textFile = sc.textFile("r.md")	# an RDD is created with this line
	> textFile.count()					# this is an Action, returns the items in RDD
	> textFile.first()					# returns the first item
	> l = textFile.filter(line => line.contains("Spark"))	# a new RDD is created
	> l.count()
### RDD usage example in Scala
	val rdd = sc.textFile("hdfs:/user/w.gz")	# take care: it is hard to parallelize GZIP -> you have to partition!
	val parsedRDD = rdd.flatMap { line =>
		line.split("""\s+""") match {
			case Array(project, _, numR, _) => Some((project, numR))
			case _ => None
		}
	}
	parsedRDD.filter { case (project, numR) => project == "en" }.
		reduceBykey(_ + _).
		take(100).
		foreach { case (project, numR) => println(s"$project: $numR") }

	// take care: the below version of the above is not as efficient!
	// please filter first, then reduce
	parsedRDD.reduceBykey(_ + _).
		filter { case (project, numR) => project == "en" }.
		take(100).
		foreach { case (project, numR) => println(s"$project: $numR") }

	//convert RDD to DataFrame, having columns "project" & "numR"
	val df = parsedRDD.toDF("project", "numR")
	df.groupBy($"page").
		agg(sum($"numR").as("count")).
		limit(100).
		show(100)

	//does the same with the SQL API
	df.registerTempTable("edits")
	sqlContext.sql("SELECT project, sum(numR) as count FROM edits LIMIT 100").show(100)

	// please filter first, then reduce
	//spark optimizes this automatically, sometimes in the DataFrame SQL query plan
	//	(RDD has no such optimizer)
	users.join(events, users("id") === events("uid"))
		.filter(events("date") > "2015-01-01")

	//DataFrame, as you see, is not type safe
	df.collect().map { row =>
		val project = row(0).asInstanceOf[String]
		val numR = row(1).asInstanceOf(Long)
	}

	//use Dataset from JSON input
	val df = sqlContext.read.json("p.json")
	case class P(name: String, age: Long)
	val ds = Dataset[P] = df.as[P]

	//API with RDD
	val lines = sc.textFile("hdfs://path/t.txt")
	val words = lines.flatMap(_.split("""\s+""")).filter(_.nonEmpty)
	val counts = words.groupBy(_.toLowerCase).map { case (w, all) => (w, all.size) }
	
	//API with DataSet
	val lines = sqlContext.read.text("hdfs://path/t.txt").as[String]
	val words = lines.flatMap(_.split("""\s+""")).filter(_.nonEmpty)  # is more effective, because of the Optimizer
	val count = words.groupBy(_.toLowerCase).count()

	rdd.setName("my").cache().count()	# cache (on nodes)! DS also can be cached
	
	ds.filter(e => (e.project == "en") && (!e.pageTitle.contains(":") && (!e.pageTitle.startsWith("."))).
		groupBy(_.pageTitle).
		reduce { (e1, e2) =>
			e1.copy(e1.project, e1.pageTitle, e1.numR + e2.numR)
		}.
		mape(_._2).
		toDF.				#convert DS back to DF
		orderBy($("numR".desc).
		as[Edit].
		take(100).
		foreach { e =>
			println(s"${e.pageTitle}: ${e.numR}")
		}
		
## Advanced API
	rdd = sc.parallelize(["a","b","c"])
	rdd = sc.textFile("/path")
	cleanedrdd = rdd.coalesce(2)					# specify the nr. of partitions
	rdd.collect()|.rdd.count()						# now execute the DAG!
	rdd.saveToCassandra()
	rdd = sc.cassandraTable("keyspace","table").select("col-1", "col-3").where("col-5 = ?", "blue")
	
### Types of RDD
	HadoopRDD, FilteredRDD, SchemaRDD, UnionRDD, JdbcRDD, JsonRDD, EdgeRDD, CassandraRDD, GeoRDD, EsSpark, ...
	
## Lifecycle of a Spark Program:
	1. create input RDD from external data or parallelize a collection in your driver program
	2. lazily transform to new RDDs (eg. .filter() or .map())
		transform functions are eg.:
			map(), flatMap, filter, sample, union, intersection, distinct, groupByKey, reduceBykey, pipe,
			coalesce, join, sortByKey, cogroup, partitionBy ...
	3. ask Spark to .cache() intermediate RDDs that will need to be reused
	4. launch actions such as .count() and .collect() to kick of the parallel computation
		action functions are eg.:
			reduce(), collect, count, first, take, takeSample, saveToCassandra, takeOrdered, saveAsTextFile,
			countBykey, foreach()
