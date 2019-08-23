# IFNULL
(MySQL specific extension), allows you to find with LIKE '%' entries having null values.

### in SQL
```sql
select * from mytable where IFNULL(firstname, '') like '%';
```
### in Java with CriteriaBuilder
```java
// define ifNull in java code:
public static <Y> Expression<Y> ifNull(CriteriaBuilder b, Class<Y> type, Expression<Y> x, Expression<Y> y)
{
    return b.function("IFNULL", type, x, y);
}
public static <Y> Expression<Y> ifElse(CriteriaBuilder b, Class<Y> type, Expression<?> exp , Expression<Y> x, Expression<Y> y)
{
    return b.function("IF", type, expression, x, y);
}

// use the ifNull Expression:
private Query createQuery()
{
    CriteriaBuilder builder = entityManager.getCriteriaBuilder();
    CriteriaQuery query = builder.createQuery();
    Root root = query.from(Entity.class);

    Path firstName = root.get(Entity.FIRST_NAME);
    Path lastName = root.get(Entity.LAST_NAME);

    Expression<String> ifNull = ifNull(builder, String.class, firstName, builder.literal(""));

    query.select(builder.tuple(year.alias(Entity.YEAR),
        builder.count(root.get(Entity.ID)).alias('count')))
        .where(builder.like(lastName, builder.parameter(String.class, Entity.LAST_NAME)),
            builder.like(ifNull, builder.parameter(String.class, Entity.FIRST_NAME)))
        .groupBy(lastName)
        .orderBy(builder.desc(lastName));

    return entityManager.createQuery(query);
}
```
# CASE
### in SQL
```sql
SELECT t0.day, COUNT(DISTINCT
    CASE
        WHEN t0.name = 'category' THEN t0.name
        ELSE t0.id
    END
    )
FROM mytable t0, mytable2 t1 WHERE

(((((t1.mytid = '6')
AND (t0.year = 2019)
)
AND (t0.category = 'MYCATEGORY')))
AND (t1.id = t0.mytid))

GROUP BY t0.day
ORDER BY t0.day DESC;
```
### in Java with CriteriaBuilder
```java
private Query createQuery()
{
    CriteriaBuilder builder = entityManager.getCriteriaBuilder();
    CriteriaQuery query = builder.createQuery();
    Root root = query.from(Entity.class);
    Path lastName = root.get(Entity.LAST_NAME);

    Expression<String> counter = builder.<String>selectCase()
            .when(builder.equal(lastName, 'acategory'), 'acategory')
            .otherwise(root.get(Entity.ID));

    query.select(builder.tuple(root.get('day').alias('day'),
        builder.count(root.get(Entity.ID)).alias('id')))
        builder.countDistinct(
            counter
        ).alias('count')))
        .where(builder.equal(root.get(Entity.YEAR), builder.parameter(Integer.class, Entity.YEAR)));

   return entityManager.createQuery(query);
}
```
### Use the above created Query (functional/stream API (java version >= 8)):
```java
private ArrayNode execQuery()
{
//execute SQL query
    Query query = createQuery();
    query.setParameter(Entity.ID, '6');
    List<Tuple> count = query.getResultList();

//groupwise sum
    Map<Integer, Long> day2Counts = count.stream().collect(
        Collectors.groupingBy((Tuple tuple) -> (Integer) tuple.get('day'),
                                Collectors.summingLong((Tuple tuple) -> (Long) tuple.get('count'))));
//reverse sort by day
    Stream<Map.Entry<Integer, Long>> day2CountsSorted = day2Counts.entrySet().stream().sorted(Map.Entry.comparingByKey(Comparator.reverseOrder()));

//map to array of node's
    ArrayNode arrayNode = JsonNodeFactory.instance.arrayNode();
    day2CountsSorted.map((Map.Entry<Integer, Long> entry) ->
        JsonNodeFactory.instance.objectNode().put('day', entry.getKey()).put('count', entry.getValue())
    ).forEach((ObjectNode objectNode) -> arrayNode.add(objectNode));

    return arrayNode;
}
```
