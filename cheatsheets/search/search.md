# Search
Infrastructure Possibilities:
1. **embedded (also on mobile devices)** solution: SQLite with the FTS3 or FTS5 Extension
1. **embedded** solution: Lucene (java, .net, C++, ...) with Tika as Content-Extractor
1. **Standarlone Server**-solution:
    1. Solr or (incl. sharding(master-slave) & replication)
        1. > $ curl http://localhost:8983/solr/update?commit=true -H "Content-Type: text/xml" -d "file.xml"
        1. cool features: highlight, spellcheck, more-like-this(&mlt=true&mlt.fl=title_t), geosearch(spatial, &fq=geo:"Intersects(POLYGON...))
        1. libs: SolrJs, SolrJ, ...
        1. **no built in security**
        1. &gt;= version 4: no schema necessary, knows dynamic fields (suffix _i will be indexed as int, _s as string)
    1. ElasticSearch
1. **Cloud** Solution:
    1. SolrCloud (is HA, **automatically** sharded, incl. replication, scalable, distributed search & indexing)

# Solr Cloud
1. Solr = **one** search server, vs. SolrCloud = **multiple** search servers
1. ui: http://localhost:8983/solr/
1. Zookeeper configuration
    1. can be  **embedded** Zookeeper (and use param zkRun: > $ java -DzkRun -jar start.jar)
    2. can be **external, standalone** (and use param zkHost: > $ java -DzkHost=localhost:9983 -jar start.jar)
    3. can be an **ensemble** (=multiple instances)
1. can "soft" commit
1. start with > $ ./bin/solr -e cloud
1. > $ java -DzkRun -DnumShards=2 -Dbootstrap_confdir=./solr/collection1/conf -Dcollection.configName=myconf -jar start.jar
    1. "zkRun" runs Zookeeper embedded (but external Zookeeper is more stable)

1. Solr **Document Routing** with document ID prefixes(="compositeId" Router) (for multitenancy):
    1. this way, you can search within a shard, without putting load on shards of other tenants
    1. don't use the 'numShards' parameter?
    1. use document-ids with a prefix (separated by a ! char), like MYPREFIX!MYDOCUMENTID
    2. search with http://localhost:8983/solr/collection1/select?q=mysearchkeyword&shard.keys=MYPREFIX{{?!}}
      (in newer solr versions, use **\_route_** instead of 'shard.keys')

## Solr **Url Commands**
1. **create** new col:
http://localhost:8983/solr/admin/collections?action=CREATE&name=mycol&numShards=3&replicationFactor=4
    1. beside CREATE, there is also DELETE or RELOAD
1. **create** new core:
http://localhost:8983/Solr/admin/cores?action=CREATE&name=mycore&instanceDir=...&config=solrconfig.xml&dataDir=data
    1. collection in clustered environment = sum of shards = logical index(=group of cores), has only meaning in a cluster
    1. collection in non-distributed environment = physical index or its replica
    1. core = physical index
1. **index**: (is done with tika inside of Solr)
curl http://localhost:8983/solr/update/extract?literal.id=doc1&commit=true -F "myfile=@my.pdf"
    1. understands a lot of file format, like json, xml, eg: 
    http://localhost:8983/solr/update -H 'content-type:application/json' -d '{{some json}}'
1. **search**
    1. http://localhost:8983/solr/select?q=myquery&start=50&rows=20&fq=filter+query&facet=on&facet.field=category&sort=dist(2,point1,point2)desc&wt=json&deftype={{lucene|dismax}}
    1. with specifying the collection to be searched through 
http://localhost:8983/solr/collection1/select?q=mysearchkeyword&collection=col1,col2
1. **get**: http://localhost:8983/solr/get?id=doc1
1. **update** (can incr, add, set)
    curl http://localhost:8983/solr/update -H 'content-type:application/json' -d '
        [
            {
                "id": "doc1",
                "field_i1": {"inc": 1},
                "field_s1": {"add": "val"},
                "field_s2": {"set": "val"},
                "field_s3": {"set": null},
            }
        ]'
1. **delete**
    1. by id: {"delete":"doc1"}
    1. by ids: {"delete":["doc1","doc2"]}
    1. by query: {"delete":{"query":"tag:category1"}}

    (you also can DELETE core's by &action=UNLOAD)

## Multitenancy strategies with Solr
1. use filterquery with your query
1. use separate collections per tenant, then search within the col (col has to be CREATE'd first)
1. use composite routing / compositeId
    1. 'Composite Hash Routing' for very large tenants, a'la MYPREFIX/2!12345 (the /2 part indicates how many bits to use in the composite hash)
1. different **cores** also could be used, depending on (non-)clustered environment setup

# SQLite & FTS5
You need to use **virtual table** (below done with sqlite3 CLI) (virtual table creates actually several other tables):
```sh
create virtual table mytable using FTS5(title,body);
insert into mytable(title,body) values('...','...');
select * from mytable where mytable match 'mykeyword' order by rank;
select title, highlight(mytable, 0, '<','>') as highlightdesc from mytable where mytable match 'mykeyword' order by rank;
```
## FTS5 can
1. Boolean operators (NOT, AND, OR) (case sensitive)
1. Phrases (")
1. Prefix queries (*)
1. NEAR: ... MATCH 'NEAR("one two" "three four", 10)'
1. Column filter
    1. ... MATCH '"colname" : one + two + three'
    1. ... MATCH '{col1 col2} : NEAR("one two" "three four", 10)'
1. Tokenizer (during indexing)
    1. can be unicode61, ascii or porter (this implements (only english) stemming), or custom
    1. CREATE VIRTUAL TABLE t1 USING fts5(x, tokenize = 'porter ascii');
    1. with **Unicode61** (this is the default), you can specify remove_diacritics, categories, tokenchars, separators
    1. with Ascii, you can specify separators
1. Helper functions
    1. **bm()**: gets score, (without params the same as **rank**)
        1. SELECT * FROM mytable WHERE mytable MATCH ? ORDER BY bm25(mytable);
    1. **highlight()**: gets highlight string, with the content of the **whole** column (specified by the int col index)
    1. **snippet(5 params)**: is similar to highlight(), except that instead of returning entire column values, it automatically selects and extracts a short fragment
1. beside **INSERT**, the **UPDATE** and **DELETE** statements are also available.
