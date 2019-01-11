# vert.x - Reactive Microservices on the JVM
    Reactive Systems are responsive, elastic, message-driven(async, only in-memory), resilient
    The Idea is from NodeJS :-) , but partly better (often can use more-than-one core!)
    Interaction uses vertx.EventBus works within or across JVMs
    web: http://vertx.io/
    Is polyglot: java, js, groovy, ruby... (everything running on the JVM)
    Is Event-Driven, has Event-Loop(using only one thread) like NodeJS
    Management and Monitoring built-in (eg. JMX)

## most basic Example:
#### in Java
```java
import io.vertx.core.Vertx;
import io.vertx.ext.web.Route;
public class My extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() throws Exception {
        vertx.createHttpserver().requestHandler(req -> req.response().end("hi")).listen(8888);
    }
}
```
#### in JS (running on Nashorn (->JVM))
```js
vertx.createHttpServer().requestHandler(function (req) {
    rq.response.end("hi");
}).listen(8888);
```

### Build & Run
```sh
# mvn plugin generates a default vertx app
mvn io.fabric8:vertx-maven-plugin:1.0.5:setup
    -DprojectGroupId=io.vertx.microservice
    -DprojectArtifactId=my
    -Dverticle.io=my.My
    -Ddependencies=web
mvn compile vertx:run

# Alternative: vertx CLI can run from java/js/... source!
vertx run My.java
vertx run My.js -cluster
```

## Example 2:
```java
public class My extends AbstractVerticle {
    @Override
    public void start() throws Exception {
        Router r = Router.router(vertx);
        //GET: use .end because we dont stream
        router.get("/api/a:param").handler(ctx -> ctx.response().end(myLongRunningFunc()));
        //GET: if you block, you have to do that explicitely
        router.get("/api/b:param").blockingHandler(this::myLongRunningBlockingFunc, false);

        //POST
        router.post("/throw").handler(request -> { throw new RuntimeException("ohh no");});

        //serve static resources
        router.route("/static/*").handler(StaticHandler.create("static"));

        //simple:
        //vertx.createHttpserver().requestHandler(router::accept).listen(8888);
        //advanced:
        vertx.createHttpserver().requestHandler(router::accept).listen(8888, result -> {
            if(result.succeeded())
                future.complete();
            else
                future.fail(result.cause());
        });
    }
    private void myLongRunningBlockingFunc(RoutingContext ctx) {
        //...
        String param = ctx.pathParam("param");
        JsonObject j = new JsonObject().put("msg", param);
        ctx.response().putHeader(Httpheaders.CONTENT_TYPE, "application/json").end(json.encore());
        //ctx.response().end(myResult);
    }
    private String myLongRunningFunc() {
        //...
        return myResult;
    }
}
```

## Publisher / Consumer
#### in Java
```java
public class MyPublisher extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() throws Exception {
        vertx.setPeriodic(1111/*delay*/, id -> {
            //...
            vertx.eventBus().publish("my-feed"/*address*/, "msg");
        });
    }
}
public class MyConsumer extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() throws Exception {
        vertx.eventBus().consumer("my-feed"/*address*/).handler(this::consume);
    }
    private void consume(Message<String> msg) {
        String sMsg = msg.body();
    }
}
```
#### in Ruby
```ruby
#Publisher
eb = $vertx.event_bus()
$vertx.set_periodic(1111) { |v|
    eb.publish("my-feed", "hi")
}

#Consumer
eb = $vertx.event_bus()
eb.consumer("my-feed") { |msg|
    puts "#{msg.body()}"
}
```

### Building Blocks:
#### Maven
```xml
<dependency>
    <groupId>io.vertx</groupId>
    <artifactId>vertx-web</artifactId>
    <version>3.5.1</version>
```
#### Java
```java
public class My {
    public static void main(String[] args) {
        Vertx vertx = Vertx.vertx();
        HttpServer s = vertx.createHttpServer();

        Router rCanOnlyGET = Router.router(vertx).route().method(HttpMethod.GET);
        Router r = Router.router(vertx);

        //accepts all request types (GET, POST...)
        Route handler1 = r.route("/").handler(routingContext -> {
            HttpServerResponse res = routingContext.response();
            if(bStream) {
                res.setchunked(true);//if you stream!
                res.write("response");
                //wait 1 sec until next
                routingContext.vertx().setTimer(1111, tid -> routingContext.next());
            } else {
                //direct response:
                res.putHeader("content-type","text/plain");
                res.end("response!");
            }
        });
        //second handler for the same route!
        Route handler2 = r.route("/").handler(routingContext -> {
            HttpServerResponse res = routingContext.response();
            res.setchunked(true);
            res.write("response 2");
            res.end();
        });

        //POST
        Route handler3 = r.post("/post/:param")
            .consumes("*/json") //accepts only json
            .handler(routingContext -> {
                res.putHeader("content-type","text/plain");
                res.end("response! " + routingcontext.request().getParam("param"));
        });

        s.requestHandler(router::accept).listen(8091);
    }
}
```
## Event Bus
    Distributed Event Bus allows communication across JVMs or complete machines.
    Both request/response and publish/subscribe
    All Vert.x instances have access to the event bus
    Verticles interact using messages
    Events/Messages are received by Handlers
```java
public class My {
    public static void main(String... args) {
        Vertx v = Vertx.vertx();
        v.deployVerticle(new MyEchoVerticle());
        v.deployVerticle(new MyWebVerticle());
    }
}
public class MyEchoVerticle extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() {
        vertx.eventBus().consumer("my-feed", msg -> {
            JsonObject j = (JsonObject)msg.body();
            j.put("k2","v2");
            msg.reply(j);
        })
    }
}
public class MyWebVerticle extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() {
        vertx.createHttpServer().requestHandler(req -> {
            JsonOjbect msg = new JsonObject().put("k1","v1");

            vertx.eventBus().send("my-feed", msg , reply-> {
                JsonObject j = (JsonObject)reply.body();
                j.put("k3","v3");
                req.response().end(j.encodePrettily());
            });
        });

        //alternative:
        vertx.createHttpServer().requestHandler(new RequestHandler()).listen(8888);
    }
    private class RequestHandler implements Handler<HttpServerRequest> {
        @Override
        public void handle(HttpServerRequest r) {
            //vert.x has RxJava API too!
            //RxJava to combine observables
            Observable<Message<String>> reply1 = vertx.eventBus().sendObservable("feed1", "msg1");
            Observable<Message<String>> reply2 = vertx.eventBus().sendObservable("feed2", "msg2");

            Observable.zip(reply1, reply2, (Message res1, Message res2) -> res1.body() +" & "+ res2.body())
                .subscribe(combinedResult -> vertx.eventBus().sendObservable("feed3", combinedResult)
                .subscribe(reply3 -> request.response().end(reply3.body())));

            //the same as one-liner:
            vertx.eventBux().sendObservable("feed1","msg1")
                .zipWith(vertx.eventBus().sendObservable("feed1","msg1"),
                (Message res1, Message res2) -> res1.body() +" & "+ res2.body())
                .subscribe(combinedResult -> vertx.eventBus().sendObservable("feed3", combinedResult)
                .subscribe(reply3 -> request.response().end(reply3.body())));
        }
    }
}
```

### EventBus into the Browser
```java
public class My {
    public static void main(String... args) {
        VertxOptions o = new VertxOptions().setClustered(true).setClusterHost("localhost");
        Vertx.clusteredVertx(o, resultHandler -> {
            Vertx v  = resultHandler.result();
            v.deployVerticle(new SockJSEventBusBridge());
            v.deployVerticle(new MyPeriodicVerticle());
            v.deployVerticle("js/my.js");
        });
    }
}
public class SockJSEventBusBridge extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() {
        Router r = Router.route(vertx);
        BridgeOptions o = new BridgeOptions().addOutboundPermitted(new PermittedOptions().setAddress("feed"));
        r.route("/eventbus/*").handler(SockJSHandler.create(vertx).bridge(o));
        r.route().handler(StaticHandler.create("static"));
        vertx.createHttpServer().requestHandler(r::accept).listen(8888);
    }
}
public class MyPeriodicVerticle extends io.vertx.core.AbstractVerticle {
    @Override
    public void start() {
        vertx.setPeriodic(1111, t -> 
        vertx.eventBus().publish("feed", "msg-from-java"));
    }
}
```
#### js/my.js
```js
vertx.setPeriodic(1111, function(id) {vertx.eventBus().publish("feed", "msg-from-js"); });
```
#### html for the browser, incl. client-side JS
```html
<script src="sockjs.js">
<script src="vertx-eventbus.js">
<script>
var eb = new EventBus("http://localhost:8888/eventbus");
eb.onopen = function() {
    eb.registerHandler("feed", function(err, msg) {
        alert(msg.body);
    }
}
</script>
```

## Microservices
    Microservice = small, runs in its own process, is distributed, is independent
    Microservice ~ Vert.x module
    Deployment tooling: https://github.com/msoute/vertx-deploy-tools
        Controlled from Jenkins

### Examples
    https://github.com/bertjan/vertx3-examples
    https://github.com/vert-x3/vertx-examples

## Advanced stuff
### ServiveDiscovery
    TODO

### Types of reactive
<img src="types.of.reactive.programing.png" width="550px">

### Types of reactive systems:
<img src="types.of.reactive.systems.png" width="550px">

### Vertext Architecture
<img src="vertex.architecture.png" width="550px">
