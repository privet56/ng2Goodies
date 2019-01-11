# Redis
1. Open Source in-memory data structure store, use as a DB or cache or message broker. Supports disk persistence.
2. Is a NoSQL Key/Value Store. Has built-in replication. Not Schema.
3. Supports several data types (string, list, set, sorted set, hash, bitmap, hyperlog, geospatial index)
4. Security: simple auth can be set up. Encryption is not supported.

## Setup / CLI
```sh
sudo apt-get install redis-server
sudo cp /etc/redis/redis.conf /etc/redis/redis.conf.default
redis-cli           # default port: 6379
> ping              # response: pong
> echo 'me'
> quit              # close connection
> set foo 100
> get foo           # returns "100"
> incr foo          # increments
> decr foo
> exists foobar     # returns 0
> get foobar        # (nil)
> del bar
> flushall
> set server:name someserver
> set server:port 8080
> expire foo 50     # 50 seconds
> ttl foo
> setex foo 30 "my" # set val & set expiration
> persist foo       # removes set ttl|expiration
> mset k1 "v1" k2 "v2"
> append foo "v3"   # appends val to old val
> rename foo bar    # renames key
> lpush foo "1"     #lpush & rpush = add to list                    LIST
> lpush foo "2"
> lrange foo 0 -1   # returns "1" & "2" (the complete list)
> llen foo          # len of the list
> lpop foo          # lpop|rpop: removes from list
> LINSERT foo BEFORE "v" "v2beInserted"
> sadd myset "v"    # add to set                                    SET
> sismember myset "v"   # is member of set?
> smembers myset    # returns all members of set
> scard myset       # returns number of eles in set
> smove myset myset2 "v"
> srem myset "v"    # remove val from set
> zadd myset 3 "v"  # members of set have score (here: 3)          SORTED-SET
> zrank myset "v"   # returns rank in order of score, of member (rank != score)
> zincrby myset 3 "v"
> hset myhash name "v"
> hget myhash name  # returns "v" value
> hgetall myhash
> hmset myhash name "v" age 39  # set all key-val pairs
> hvals             # retuns all values
> hincrby myhash age 1
> hdel myhash age
```
## Persistence
Persistence types: RDB or AOF(append-only-file, see redis.conf:appendonly)
```sh
save                    # creates snapshot to disk (/var/lib/redis/dump.rdb)
save 6000               # saves every 6000 seconds
```
## Config = /etc/redis/redis.conf
```ini
appendonly yes  # def: no
```

## Usage with NodeJS
```sh
npm install redis express body-parser method-override express-handlebars --save
npm start   # if you wanna start command defined in package.json:scripts:start: "node app"
```
app.js
```js
const exress = require("express");
const exphbs = require("express-handlebars");
const path = require("path");
const bodyParser = require("body-parser");
const methodOverride = require("method-override");
const app = express();

const redis = require("redis");
let client = redis.createClient();
client.on('connect', function() {console.log('connected');});

app.engine("handlebars", exphbs({defaultLayout:'main'}));   //view: main.handbars
app.set('view engine', 'handlebars');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));
app.use(methodOverride('_method'));                         //we set post param name
app.get('/', function(req, res,next) {
    res.render("search");
});
app.get('/add', function(req, res,next) {
    res.render("add");
});
app.post('/', function(req, res,next) {
    let id = req.body.id;
    client.hgetall(id, function(error, o) {
        if(!o) {
            return res.render("search", {
                error: 'not found'
            }
        }
        res.render('details', {
            details: o
        })
    });
});
app.post('/add', function(req, res,next) {
    let id = req.body.id;
    let name = req.body.name;
    client.hmset(id, ['name',name], function(error, reply) {
        if(error) {/*do error handling*/}
        res.redirect('/?op=add&result=success');
    });
});
app.del('/del:id', function(req, res,next) {
    let id = req.params.id;
    client.del(id);
    res.redirect('/?op=del&result=success');
});

app.listen(3333, function() {
    console.log("started");
});
```
views/layout/main.handlebars
```html
...
<body>{{{body}}}</body>
```
views/search.handlebars
```html
{{#if error}} {{error}}{{/if}}
<form method=post>
    <!-- Complete with: name search, ... -->
    <input name=id>
</form>
```
views/add.handlebars
```html
{{#if error}} {{error}}{{/if}}
<form method=post>
    <!-- Complete with: label, ... -->
    <input name=id>
    <input name=name>
</form>
```

views/details.handlebars
```html
{{#if error}} {{error}}{{/if}}
<!-- Complete with: name output, ... -->
<div>{{o.name}}</div>
<form method=post, action='del/{{o.id}}?_method=DELETE'>
<input type=submit class="btn btn-danger pull-right" value="delete!">
</form>
```
