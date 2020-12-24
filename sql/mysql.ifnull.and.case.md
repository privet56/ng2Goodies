# IFNULL
(MySQL specific extension), allows you to find with LIKE '%' entries having null values.

### In SQL
```sql
select * from mytable where IFNULL(firstname, '') like '%';
```
### In Java with CriteriaBuilder
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

private final static Logger logger = LoggerFactory.getLogger(MethodHandles.lookup().lookupClass());

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
### In SQL
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
### In Java with CriteriaBuilder
If using EclipseLink: take care, as its CriteriaBuilder implementation is buggy (not threadsafe!)!
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
public void initialize(@Observes InitializeEvent event)
{
    //on startup, register SQL query
    event.registerQuery('MYQUERY', createQuery());
}
private ArrayNode execQuery()
{
//execute SQL query
    Query query = entityManager.createNamedQuery('MYQUERY');
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
# MySQL - Slow Query Analysis
```sql
-- activate slow query logging on MySQL/MariaDB in the mysql console:
-- (settings will be reset when mysqld restarted!)
SET GLOBAL slow_query_log = 'ON';
SET GLOBAL slow_query_log_file = 'c:/temp/slowqueries.log';
SET GLOBAL long_query_time = 0.33;	-- long queries last longer than 0.33 sec
SET GLOBAL log_queries_not_using_indexes = 1;

-- test (after logout/login)
SELECT SLEEP(0.66); -- lasts longer than 0.33 sec -> will log!
```
### Analyze created log
> pt-query-digest.pl c:/temp/slowqueries.log

# MySQL - Foreign Key
```sql
-- CREATE foreign key
ALTER TABLE t1 ADD t2_id VARCHAR(50);
ALTER TABLE t1 ADD CONSTRAINT t1_to_t2 FOREIGN KEY (t2_id) REFERENCES t2 (id);

-- CHANGE foreign key make it 'NOT NULL'
ALTER TABLE t1 MODIFY COLUMN t2_id VARCHAR(50) NOT NULL;

-- DELETE (first key, then column)
ALTER TABLE t1 DROP FOREIGN KEY t1_to_t2;
ALTER TABLE t1 DROP COLUMN t2_id;
DELETE FROM _flyway WHERE script = 'V1__foreignKey.sql';
```

# Repository base class
DB Repository base class for java Enterprise Apps, with general functions like exist:<br>
(Spring offers already Repo base classes with such general functionality)
```java
public <E extends BaseEntity> boolean exists(final Class<E> entityClass, final String id) { ...
public <E extends BaseEntity> List<E> findAll(final Class<E> entityClass) { ...
public <E extends BaseEntity> List<String> findAllIds(final Class<E> entityClass) { ...
public <E extends BaseEntity> int deleteAll(final Class<E> entityClass) { ...
public <E extends BaseEntity> E findById(final Class<E> entityClass, final String id) { ...
public <E extends BaseEntity> E create(final Class<E> entityClass, Consumer<E> consumer) { ...
```
[ServiceRepository.java](ServiceRepository.java)

# Query by Relation Count
```sql
SELECT t0.id, COUNT(DISTINCT(t1.id)) FROM
MyEntity t0 left outer join MySubEntity t1 on t1.myentity_id = t0.id
group by t0.id
HAVING (COUNT(DISTINCT(t1.id)) < ?)
```
```java
private Query createFindEntityIDsWithLessSubEntityCountQuery() {

        CriteriaBuilder builder = entityManager.getCriteriaBuilder();
        CriteriaQuery query = builder.createQuery();
        Root<MyEntity> root = query.from(MyEntity.class);
        Path mySubEntitiesPath = root.join(MyEntity.MySubEntities, JoinType.LEFT);

        query.select(root.get(BaseEntity.ID)).
                groupBy(root.get(BaseEntity.ID)).
                having(builder.lessThan(
                    builder.countDistinct(mySubEntitiesPath),
                    (builder.parameter(Long.class, 'count'))
                ));

        return entityManager.createQuery(query);
}
```
# Query for latest Date
```sql
    select d.created_at from tblm m
        join tble e on m.id = e.m_id
        join tbld d on d.e_id = e.id
        where m.id = 'mid'
        order by d.created_at desc
        limit 1;
-- more performant alternative:
    select max(d.created_at) from tblm m
        join tble e on m.id = e.m_id
        join tbld d on d.e_id = e.id
        where m.id = 'mid';
```
```java
    private Query createFindLastDateQuery(boolean useTheMaxSqlFunction) {
        CriteriaBuilder builder = entityManager.getCriteriaBuilder();
        CriteriaQuery query = builder.createQuery();
        Root<Tblm> root = query.from(Tblm.class);

        Join<Tblm, Tble> tbleJoin = root.join(Tblm.E);
        Join<Tble, Tbld> tbldJoin = tbleJoin.join(Tble.D);

        if (useTheMaxSqlFunction) {
            query.select(builder.max(tbldJoin.get(Tbld.CREATED_AT)))
                .where(builder.equal(root.get(BaseEntity.ID), builder.parameter(String.class, BaseEntity.ID)));

            return entityManager.createQuery(query);
        }

        query.select(tbldJoin.get(Tbld.CREATED_AT))
            .where(builder.equal(root.get(BaseEntity.ID), builder.parameter(String.class, BaseEntity.ID)))
            .orderBy(builder.desc(tbldJoin.get(Tbld.CREATED_AT)));

        return entityManager.createQuery(query).setMaxResults(1); //LIMIT 1 = take only newest date!
    }
```
# Find groupwise max timestamp with SubQuery
```sql
SELECT mytbl.id, mytbl.id1_column, mytbl.id2_column, mytbl.id3_column, mytbl.timestamp_column
	FROM tablename mytbl
WHERE (mytbl.id1_column, mytbl.id2_column, mytbl.id3_column, mytbl.timestamp_column)
IN	(
		SELECT maxtbl.id1_column, maxtbl.id2_column, maxtbl.id3_column, max(maxtbl.timestamp_column)
		FROM tablename maxtbl
		GROUP BY maxtbl.id1_column, maxtbl.id2_column, maxtbl.id3_column
	)
-- AND mytbl.id1_column LIKE '20253%'
-- AND mytbl.id2_column LIKE '1%'
-- AND mytbl.id3_column LIKE '1%'
GROUP BY mytbl.id1_column, mytbl.id2_column, mytbl.id3_column
ORDER BY mytbl.timestamp_column DESC;
```
```java
private Query createFindGroupwiseMaxQuery() {
	CriteriaBuilder builder = entityManager.getCriteriaBuilder();
	CriteriaQuery query = builder.createQuery();
	Root<MyTbl> root = query.from(MyTbl.class);

	Subquery<String> subQuery = query.subquery(String.class);
	Root<MyTbl> subQueryRoot = subQuery.from(MyTbl.class);

	Expression concatFun = builder.function("CONCAT", String.class,
											root.get(MyTbl.ID1),
											root.get(MyTbl.ID2),
											root.get(MyTbl.ID3),
											root.get(MyTbl.TIMESTAMP));

	Expression concatMaxFun = builder.function("CONCAT", String.class,
											subQueryRoot.get(MyTbl.ID1),
											subQueryRoot.get(MyTbl.ID2),
											subQueryRoot.get(MyTbl.ID3),
											builder.max(subQueryRoot.get(MyTbl.TIMESTAMP)));

	Subquery<MyTbl> subQueryFun = subQuery
					 .select(concatMaxFun)
					 .where(
						builder.like(subQueryRoot.get(MyTbl.ID1), builder.parameter(String.class, MyTbl.ID1)),
						builder.like(subQueryRoot.get(MyTbl.ID2), builder.parameter(String.class, MyTbl.ID2)),
						builder.like(subQueryRoot.get(MyTbl.ID3), builder.parameter(String.class, MyTbl.ID3))
					 )
					 .groupBy(
						subQueryRoot.get(MyTbl.ID1),
						subQueryRoot.get(MyTbl.ID2),
						subQueryRoot.get(MyTbl.ID3));

	query.select(root.get(MyTbl.ID)).where(
		builder.in(concatFun).value(subQueryFun)
	//sort hard-coded by timestamp, there is no possibility to sort dynamically by builder.parameter
	).orderBy(builder.desc(root.get(MyTbl.TIMESTAMP)));

	return entityManager.createQuery(query);
}
```
