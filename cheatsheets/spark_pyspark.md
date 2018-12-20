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
spark=SparkSession.builder.appName('d').getOrCreate()
df=spark.read.csv('d.csv',inferSchema=True, header=True)
df.columns  # [Out]: ['r', 'age', 'exp', 'fam', 'mob']
df.printSchema()
df.show(3)
df.select('age','mob').show(5)
df.describe().show()
print((df.count),(len(df.columns))  # [Out]: ( 33,5)

df.coalesce(1).write.format("csv").option("header","true").save("/tmp/m.csv")
df.write.format('parquet').save("/tmp/m")
```
## Data Adjustment, Select, Filter, count =  Exploratory Data Analysis
```python
df.withColumn("age_after_10_yrs",(df["age"]+10)).show(10,False)
from pyspark.sql.types import StringType,DoubleType
df.withColumn('age_double',df['age'].cast(DoubleType())).show(10,False)
df.filter(df['mob']=='Vi').show()
df.filter(df['mob']=='Vi').select('age','r', 'mob').show()
df.filter(df['mob']=='Vi').filter(df['exp'] > 10).show()
df.filter((df['mob']=='Vi')&(df['exp'] >10)).show()
df.select('mob').distinct().show()
df.select('mob').distinct().count()
df.groupBy('mob').count().show(5,False)
df.groupBy('mob').count().orderBy('count',ascending=False).show(5,False)
df.groupBy('mob').mean().show(5,False)
df.groupBy('mob').sum().show(5,False)
df.groupBy('mob').max().show(5,False)
df.groupBy('mob').agg({'exp':'sum'}).show(5,False)
from pyspark.sql.functions import udf   # User-Defined Functions (UDFs)
brand_udf=udf(price_range,StringType())
df.withColumn('price_range',brand_udf(df['mob'])).show(10,False)
age_udf = udf(lambda age: "young" if age <= 30 else"senior", StringType())
df.withColumn("age_group", age_udf(df.age)).show(10,False) 
from pyspark.sql.functions import pandas_udf
length_udf = pandas_udf(remaining_yrs, IntegerType())
df.withColumn("yrs_left", length_udf(df['age'])).show(10,False)
prod_udf = pandas_udf(prod, DoubleType())
df.withColumn("product",prod_udf(df['r'], df['exp'])).show(10,False)
df=df.dropDuplicates()
df_new=df.drop('mob')

from pyspark.sql.functions import rand
df.orderBy(rand()).show(10,False)

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

test_predictions = lr_model.evaluate(test_df)
print(test_results.r2) # [Out]: 0.87
print(test_results.meanSquaredError) # [Out]: 0.00014
```
# Logistic Regression
```python
from pyspark.ml.feature import StringIndexer
from pyspark.ml.feature import VectorAssembler
se_indxr = StringIndexer(inputCol="se",   OutputCol="se_Num").fit(df)
df = se_indxr.transform(df)
df.show(3,False)
df.groupBy('se').count().orderBy('count', ascending=False).show(5,False)
from pyspark.ml.feature import OneHotEncoder
search_engine_encoder=OneHotEncoder(inputCol="se_Num", outputCol="se_Vector")
df = search_engine_encoder.transform(df)
df.groupBy('se_Vector').count().orderBy('count', ascending=False).show(5,False)
country_encoder = OneHotEncoder(inputCol="co_Num", outputCol="co_Vector")
df = country_encoder.transform(df)
df.select(['co','co_Num','co_Vector']).show(3,False)
df.groupBy('co_Vector').count().orderBy('count', ascending=False).show(5,False)
df_assembler = VectorAssembler(inputCols=['se_Vector','co_Vector','Age', 'RepeatVisit', 'pagevw'], outputCol="features")
df = df_assembler.transform(df)
df.select(['features','Status']).show(10,False)
model_df = df.select(['features','Status'])
training_df,test_df = model_df.randomSplit([0.75,0.25])
from pyspark.ml.classification import LogisticRegression
log_reg = LogisticRegression(labelCol='Status').fit(training_df)
train_results = log_reg.evaluate(training_df).predictions
train_results.filter(train_results['Status']==1).filter(train_results['prediction']==1).select(['Status', 'prediction','probability']).show(10,False)
results = log_reg.evaluate(test_df).predictions
results.select(['Status','prediction']).show(10,False)

tp = results[(results.Status == 1) & (results.prediction == 1)].count()
tn = results[(results.Status == 0) & (results.prediction == 0)].count()
fp = results[(results.Status == 0) & (results.prediction == 1)].count()
fn = results[(results.Status == 1) & (results.prediction == 0)].count()

accuracy    = float(true_postives + true_negatives) / (results.count())
recall      = float(true_postives) / (true_postives + false_negatives)
precision   = float(true_postives) / (true_postives + false_positives)
```
# Random Forest
```python
from pyspark.ml.feature import VectorAssembler
df_assembler = VectorAssembler(inputCols=['rate_mrr', 'age', 'yrs_mrr', 'chldr', 'reli'], outputCol="features")
df = df_assembler.transform(df)
model_df = df.select(['features','affrs'])
train_df,test_df=model_df.randomSplit([0.75,0.25])
from pyspark.ml.classification import RandomForestClassifier
rf_classifier = RandomForestClassifier(labelCol='affrs', numTrees=50).fit(train_df)
rf_predictions = rf_classifier.transform(test_df)
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
from pyspark.ml.evaluation import BinaryClassificationEvaluator
rf_accuracy = MulticlassClassificationEvaluator(labelCol='affrs',metricName='accuracy').evaluate(rf_predictions)
print('The accuracy of RF on test data is {0:.0%}'.format(rf_accuracy))
rf_precision = MulticlassClassificationEvaluator(labelCol='affrs',metricName='weightedPrecision').evaluate(rf_predictions)
print('The precision rate on test data is {0:.0%}'.format(rf_precision))
rf_auc = BinaryClassificationEvaluator(labelCol='affrs').evaluate(rf_predictions)
rf_classifier.featureImportances
df.schema["features"].metadata["ml_attr"]["attrs"]
```
## Save / Load
```python
from pyspark.ml.classification import RandomForestClassificationModel
rf_classifier.save("/home/RF_model")
rf = RandomForestClassificationModel.load("/home/RF_model")
new_preditions = rf.transform(new_df)
```

# Recommender
```python
from pyspark.sql.functions import *
from pyspark.ml.feature import StringIndexer, IndexToString
stringIndexer = StringIndexer(inputCol="title", outputCol="title_new")
model = stringIndexer.fit(df)
indexed = model.transform(df)
train,test = indexed.randomSplit([0.75,0.25])
from pyspark.ml.recommendation import ALS
rec = ALS(maxIter=10,regParam=0.01,userCol='userId', itemCol='title_new',ratingCol='rating',nonnegative=True, coldStartStrategy="drop")
rec_model = rec.fit(train)
predicted_ratings = rec_model.transform(test)

from pyspark.ml.evaluation import RegressionEvaluator
evaluator = RegressionEvaluator(metricName='rmse' predictionCol='prediction',labelCol='rating')
rmse = evaluator.evaluate(predictions)
print(rmse) # [Out]: 1.0293

unique_movies = indexed.select('title_new').distinct()
a = unique_movies.alias('a')
watched_movies = indexed.filter(indexed['userId'] == user_id).select('title_new').distinct()
b = watched_movies.alias('b')
total_movies = a.join(b, a.title_new == b.title_new, how='left')
remaining_movies = total_movies.where(col("b.title_new").isNull()).select(a.title_new).distinct()
remaining_movies = remaining_movies.withColumn("userId",lit(int(user_id)))
recommendations = rec_model.transform(remaining_movies).orderBy('prediction',ascending=False)
movie_title = IndexToString(inputCol="title_new", outputCol="title", labels=model.labels)
final_recommendations = movie_title.transform(recommendations)
```
# Clustering
## KMeans
```python
from pyspark.ml.clustering import KMeans
errors=[]
for k in range(2,10):
    kmeans = KMeans(featuresCol='features',k=k)
    model = kmeans.fit(final_data)
    intra_distance = model.computeCost(final_data)
    errors.append(intra_distance)

kmeans = KMeans(featuresCol='features',k=3)
model = kmeans.fit(final_data)
model.transform(final_data).groupBy('prediction').count().show()
predictions = model.transform(final_data)
predictions.groupBy('species','prediction').count().show()
```
### Plot
```python
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
cluster_number = range(2,10)
plt.xlabel('Number of Clusters (K)')
plt.ylabel('SSE')
plt.scatter(cluster_number,errors)
plt.show()  # you can see on the 'elbow' method, which cluster size is best

pandas_df = predictions.toPandas()
pandas_df.head()
from mpl_toolkits.mplot3d import Axes3D
cluster_vis = plt.figure(figsize=(12,10)).gca(projection='3d')
cluster_vis.scatter(pandas_df.sepal_length, pandas_df.sepal_width, pandas_df.petal_length, c=pandas_df.prediction,depthshade=False)
plt.show()

```
# NLP, Natural Language Processing
```python
df=spark.createDataFrame([
    (1,'liked a lot'),
    (2,'liked'),
    (3,'was alright'),
    (4,'not good')],
    ['user_id','review'])

from pyspark.ml.feature import Tokenizer
tokenization = Tokenizer(inputCol='review',outputCol='tokens')
tokenized_df = tokenization.transform(df)
from pyspark.ml.feature import StopWordsRemover
stopword_removal = StopWordsRemover(inputCol='tokens', outputCol='refined_tokens')
refined_df = stopword_removal.transform(tokenized_df)
refined_df.select(['user_id','tokens','refined_tokens']).show(4,False)

from pyspark.ml.feature import CountVectorizer
count_vec = CountVectorizer(inputCol='refined_tokens', outputCol='features')
cv_df = count_vec.fit(refined_df).transform(refined_df)
cv_df.select(['user_id','refined_tokens','features']).show(4,False)

count_vec.fit(refined_df).vocabulary

# TF-IDF
from pyspark.ml.feature import HashingTF, IDF
hashing_vec = HashingTF(inputCol='refined_tokens', outputCol='tf_features')
hashing_df = hashing_vec.transform(refined_df)
hashing_df.select(['user_id','refined_tokens', 'tf_features']).show(4,False)
tf_idf_vec = IDF(inputCol='tf_features',outputCol='tf_idf_features')
tf_idf_df = tf_idf_vec.fit(hashing_df).transform(hashing_df)
tf_idf_df.select(['user_id','tf_idf_features']).show(4,False)

# Text Classification
text_df = text_df.withColumn("Label", text_df.Sentiment.cast('float')).drop('Sentiment')
from pyspark.sql.functions import length
text_df = text_df.withColumn('length',length(text_df['Review']))
text_df.groupBy('Label').agg({'Length':'mean'}).show()
tokenization = Tokenizer(inputCol='Review',outputCol='tokens')
tokenized_df = tokenization.transform(text_df)
stopword_removal = StopWordsRemover(inputCol='tokens',  outputCol='refined_tokens')
refined_text_df = stopword_removal.transform(tokenized_df)
from pyspark.sql.functions import udf
from pyspark.sql.types import IntegerType
from pyspark.sql.functions import *
len_udf = udf(lambda s: len(s), IntegerType())
refined_text_df = refined_text_df.withColumn("token_count", len_udf(col('refined_tokens')))
refined_text_df.orderBy(rand()).show(10)
count_vec = CountVectorizer(inputCol='refined_tokens', outputCol='features')
cv_text_df = count_vec.fit(refined_text_df).transform(refined_text_df)
cv_text_df.select(['refined_tokens','token_count','features', 'Label']).show(10)
model_text_df = cv_text_df.select(['features', 'token_count','Label'])
rom pyspark.ml.feature import VectorAssembler
df_assembler = VectorAssembler(inputCols=['features', 'token_count'], outputCol='features_vec')
model_text_df = df_assembler.transform(model_text_df)
from pyspark.ml.classification import LogisticRegression
training_df, test_df = model_text_df.randomSplit([0.75,0.25])
log_reg = LogisticRegression(featuresCol='features_vec', labelCol='Label').fit(training_df)
results = log_reg.evaluate(test_df).predictions
results.show()

from pyspark.ml.evaluation import BinaryClassificationEvaluator
true_postives   = results[(results.Label == 1) & (results.prediction == 1)].count()
true_negatives  = results[(results.Label == 0) & (results.prediction == 0)].count()
false_positives = results[(results.Label == 0) & (results.prediction == 1)].count()
false_negatives = results[(results.Label == 1) & (results.prediction == 0)].count()

recall      = float(true_postives) / (true_postives + false_negatives)
precision   = float(true_postives) / (true_postives + false_positives)
accuracy    = float(true_postives + true_negatives) / (results.count())
```
## Sequence Embedding
```python
df.select(['user_id','page','visit_number','time_spent', 'converted']).show(10,False)
w = Window.partitionBy("user_id").orderBy('timestamp')
df = df.withColumn("previous_page", lag("page", 1, 'started').over(w))
df.select('user_id','timestamp','previous_page','page').show(10,False)
def indicator(page, prev_page):
    if page == prev_page:
        return 0
    else:
        return 1
page_udf = udf(indicator,IntegerType())
df = df.withColumn("indicator", page_udf(col('page'), col('previous_page')).withColumn('indicator_cummulative', sum(col('indicator')).over(w))
df.select('previous_page','page','indicator', 'indicator_cummulative').show(20,False)
w2 = Window.partitionBy(["user_id",'indicator_cummulative']).orderBy('timestamp')
df = df.withColumn('time_spent_cummulative', sum(col('time_spent')).over(w2))
df.select('timestamp','previous_page','page', 'indicator','indicator_cummulative','time_spent', 'time_spent_cummulative').show(20,False)

aggregations = []
aggregations.append(max(col('final_page')).alias('page_emb'))
aggregations.append(max(col('final_time_spent')).alias('time_spent_emb'))
aggregations.append(max(col('converted')).alias('converted_emb'))
dfEmb = df.select(['user_id','indicator_cummulative', 'final_page','final_time_spent','converted']).groupBy(['user_id','indicator_cummulative']).agg(*aggregations)
w4 = Window.partitionBy(["user_id"]).orderBy('indicator_cummulative')
w5 = Window.partitionBy(["user_id"]).orderBy(col('indicator_cummulative').desc())

dfEmb = dfEmb.withColumn('journey_page', collect_list(col('page_emb')).over(w4))\
 .withColumn('journey_time_temp', collect_list(col('time_spent_emb')).over(w4)) \
 .withColumn('journey_page_final', first('journey_page').over(w5)) \
 .withColumn('journey_time_final', first('journey_time_temp').over(w5)) \
 .select(['user_id','journey_page_final', 'journey_time_final','converted_emb'])

dfEmb = dfEmb.dropDuplicates()
dfEmb.count()
dfEmb.select('user_id').distinct().count()
dfEmb.select('user_id','journey_page_final','journey_time_final').show(10)

pd_df_emb0 = dfEmb.toPandas()
pd_dfEmb = pd_dfEmb.reset_index(drop=True)
!pip install gensim
from gensim.models import Word2Vec
EMBEDDING_SIZE = 100
model = Word2Vec(pd_dfEmb['journey_page_final'], size=EMBEDDING_SIZE)
print(model) # [Out]: Word2Vec(vocab=7, size=100, alpha=0.025)
page_categories = list(model.wv.vocab)
print(page_categories) # [Out]: ['pinf', 'home', 'added2crt', 'others', 'reviews', 'offers', 'buy']
model['offers'].shape # [Out]: (100,)

pca = PCA(n_components=2)   # dimensionality reduction technique (PCA)
result = pca.fit_transform(X)
plt.figure(figsize=(10,10))
plt.scatter(result[:, 0], result[:, 1])
for i,page_category in enumerate(page_categories):
    plt.annotate(page_category,horizontalalignment='right', verticalalignment='top',xy=(result[i, 0], result[i, 1]))
plt.show()
```
