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
      (in newer solr versions, use '_route_' instead of 'shard.keys')

## Solr **Url Commands**
1. **create** new col:
http://localhost:8983/solr/admin/collections?action=CREATE&name=mycol&numShards=3&replicationFactor=4
    1. beside CREATE, there is also DELETE or RELOAD
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
