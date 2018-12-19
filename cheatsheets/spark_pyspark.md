<link rel="stylesheet" href="_github-markdown.css">

# PySpark

## First Steps: Check if Setup OK
    export SPARK_PATH=~/spark-2.3.0-bin-hadoop2.7
    export PYSPARK_DRIVER_PYTHON="jupyter"
    export PYSPARK_DRIVER_PYTHON_OPTS="notebook"
    alias notebook='$SPARK_PATH/bin/pyspark --master local[2]'
```python
import findspark
findspark.init()
import pyspark
from pyspark.sql import SparkSession
spark=SparkSession.builder.getOrCreate()
```
## Data Input / Output
```python
from pyspark.sql import SparkSession
spark=SparkSession.builder.appName('data_processing').getOrCreate()
df=spark.read.csv('sample_data.csv',inferSchema=True, header=True)
df.columns  # [Out]: ['ratings', 'age', 'experience', 'family', 'mobile']
df.printSchema()
df.show(3)
df.select('age','mobile').show(5)
df.describe().show()
print((df.count),(len(df.columns))  # [Out]: ( 33,5)

df.coalesce(1).write.format("csv").option("header","true").save("/tmp/m.csv")
df.write.format('parquet').save("/tmp/m")
```
## Data Adjustment, Select, Filter, count
```python
df.withColumn("age_after_10_yrs",(df["age"]+10)).show(10,False)
from pyspark.sql.types import StringType,DoubleType
df.withColumn('age_double',df['age'].cast(DoubleType())).show(10,False)
df.filter(df['mobile']=='Vivo').show()
df.filter(df['mobile']=='Vivo').select('age','ratings', 'mobile').show()
df.filter(df['mobile']=='Vivo').filter(df['experience'] > 10).show()
df.filter((df['mobile']=='Vivo')&(df['experience'] >10)).show()
df.select('mobile').distinct().show()
df.select('mobile').distinct().count()
df.groupBy('mobile').count().show(5,False)
df.groupBy('mobile').count().orderBy('count',ascending=False).show(5,False)
df.groupBy('mobile').mean().show(5,False)
df.groupBy('mobile').sum().show(5,False)
df.groupBy('mobile').max().show(5,False)
df.groupBy('mobile').agg({'experience':'sum'}).show(5,False)
from pyspark.sql.functions import udf   # User-Defined Functions (UDFs)
brand_udf=udf(price_range,StringType())
df.withColumn('price_range',brand_udf(df['mobile'])).show(10,False)
age_udf = udf(lambda age: "young" if age <= 30 else"senior", StringType())
df.withColumn("age_group", age_udf(df.age)).show(10,False) 
from pyspark.sql.functions import pandas_udf
length_udf = pandas_udf(remaining_yrs, IntegerType())
df.withColumn("yrs_left", length_udf(df['age'])).show(10,False)
prod_udf = pandas_udf(prod, DoubleType())
df.withColumn("product",prod_udf(df['ratings'], df['experience'])).show(10,False)
df=df.dropDuplicates()
df_new=df.drop('mobile')
```
# Linear Regression
```python
from pyspark.ml.linalg import Vector
from pyspark.ml.feature import VectorAssembler
vec_assmebler=VectorAssembler(inputCols=['var_1','var_2', 'var_3', 'var_4', 'var_5'], outputCol='features')
features_df=vec_assmebler.transform(df)
model_df=features_df.select('features','output')
train_df, test_df = model_df.randomSplit([0.7,0.3])

from pyspark.ml.regression import LinearRegression
lin_Reg = LinearRegression(labelCol='output')
lr_model = lin_Reg.fit(train_df)
print(lr_model.coefficients)
print(lr_model.intercept)
training_predictions = lr_model.evaluate(train_df)
print(training_predictions.r2)

test_predictions=lr_model.evaluate(test_df)
print(test_results.r2) # [Out]: 0.87
print(test_results.meanSquaredError) # [Out]: 0.00014
```
# Logistic Regression
```python

```