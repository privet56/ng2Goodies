# Hazelcast
    Hazelcast = in-memory distributed cache for the JVM
    Has a data-grid = data can be shared between nodes (like gemfire).
    Is masterless (like Cassandra)
    Cluster with data-partitions in Nodes.
    Example: share a HashMap across JVMs
    Supports publish/subscribe.
    Supports JVM languages, C++, NodeJS
    Is a single 5 MB Jar file, no dependencies
    Can run stand-alone or embedded
    used for session/state sharing, Messaging, distributed caching, distributed processing
    Native Java, has REST and Memcache interfaces
## Usage
```java

Config cfg = new Config();
//several instances on the same JVM possible
HazelcastInstance hazelcastServer1 = Hazelcast.newHazelcastInstance(cfg);
HazelcastInstance hazelcastServer2 = Hazelcast.newHazelcastInstance(cfg);
HazelcastInstance hazelcastClient  = HazelcastClient.newHazelcastClient();

import com.hazelcast.core.*;
Map m = hazelcast.getMap("mymap");
m.put("1","2");             //all serializable Object's are allowed
m.putIfAbsent("1", "2");    //java.util.ConcurrentMap methods are atomic
m.replace("1", "2");

//MultiMap = one key, multiple values!
MultiMap<String, MyClass> m = hazelcast.getMultiMap("mm"):
Collection<MyClass> c = m.get("1");
boolean removed = m.remove("1", new MyClass());

//Distributed Queue
{
    BlockingQueue<MyClass> q = hazelcast.getQueue("t");
    q.offer(my);
    MyClass m = q.poll();
    q.offer(my, 500 ,TimeUnit.MILLISECONDS);
    MyClass my = q.poll(5, TimeUnit.SECONDS);
    q.put(my);
    MyClass my = q.take();  //indefinitely blocking operation!
}
//Distributed Lock (can only be timed-operation!)
{
    Lock l = hazelcast.getLock(myLockObject);
    l.lock();
    l.unlock();//in try-finally!
    IMap<String, MyClass> m = hazelcast.getMap("m");
    m.lock("1");
    m.unlock("1");//in try-finally!
}
// advanced API:
Cluster c = hazelcast.getCluster();
cluster.addMembershipListener(l);
Member localMember = cluster.getLocalMember();
System.out.println(localMember.getInetAddress());
Set<Member> members = cluster.getMembers();
```
Maven:
```xml
<dependency>
    <groupId>com.hazelcast</groupId>
    <artifactId>hazelcast</artifactId>
    <version>3.5</version>
```
Run Sever in Console (port: 5701):
```sh
#!/bin/sh
# you can fire it up several times! they automatically will know each other
 java -server -Djava.net.preferIPvStack=true, -cp hazelcast-all-3.5.jar com.hazelcast.console.ConsoleApp

 > m.put 1 bla  # m.put = map put
 > m.get 1      # returns bla
 > m.lock 1     # '1' cannot be updated now
 > m.addListener
 > q.take       # blocks & listens and 
 > q.offer bla  # q.take will receive bla
 > q.put
 > m.size
 > t.publish msg # listener (.addListener) receives
```
### Web Interface
Hazelcast Management Console:
http://admin:admin@localhost:8080/mancenter-3.2.3/
  shows nodes, maps, queues, topics, multimaps, executors, members(=clients)

## Features & Gotchas
1. is thread-safe. hazelcast.getMap("1"), hazelcast.getList("mylist")
2. all objects must be serializable:
    1. java.io.Serializable
    2. com.hazelcast.nio.DataSerializable //better because faster
3. Hazelcast.getExecutorService().execute(new DistributedTask(runnable, "key"));
4. Data Affinity: same key -> same node! (independently of object you call on)
```java
hz.getMap("ma").get("key");
hz.getMap("mb").put("key", "2");    //works on the same node as line above
hz.getLock("key").lock();           //works on the same node as line above
```

## Listener / Transactions
```java
import com.hazelcast.core.*;

public class MyMsgListener implementes MessageListener {
    public static void main(String[] args) {
        MyMsgListener m = new MyMsgListener();
        ITopic<String> topic = hazelcast.getTopic("t");
        topic.addMessageListener(m);
        topic.publish("my");
    }
    public void onMessage(Message<String> msg) {
        System.out.println(msg.getMessageObject());
    }
}

//listen to distributed events
public class MyEntryListener implements EntryListener {
    public static void main(String[] args) {
        MyEntryListener l = new MyEntryListener();
        IMap m = hazelcast.getMap("m");
        m.addEntryListener(l, true);
        m.addEntryListener(l, "key");
    }
    public void entryAdded(EntryEvent e) {
        System.out.println(e.getKey() ++" > " + e.getValue());
    }
    public void entryRemoved(EntryEvent e) { }
    public void entryUpdated(EntryEvent e) { }

}
//Transactions: do all or nothing!
{
    TransactionOptions o = new TransactionOptions().setTransactionType(TransactionType.TWO_PHASE);
    TransactionContext c = hz.newTransactioncontext(o);
    c.beginTransaction();
    TransactionalQueue tq = c.getQueue("myq");
    TransactionalMap tm   = c.getMap("mym");
    TransactionalSet ts   = c.getSet("mys");
    try {
        Object o = tq.poll();
        tm.put("1", "2");
        ts.add("1");
        c.commitTransaction();
    } catch(Throwable t) {
        c.rollbackTransaction();
    }
}
```
### Control Partition Assignment: PartitionAware
```java
public class MyKey implements Serializable, PartitionAware {
    private int myId;
    ...
    public Object getPartitionKey() {
        return myId;
    }
}
//use:
hz.getMap("m").put(new Mykey(1), myValue);
```

### ExecutorService
```java
public class MyTask implements Callable<String>, Serializable {
    @Override
    public String call() {
        return "my";
    }
}
//use:
ExecutorService es = hz.getExecutorService();
Future<String> f = es.submit(new MyTask());
...
String result = f.get();

Member member = ...;
Set<Member> members = ...;
FutureTask<String> t = null;
t = new DitributedTask<String>(new MyTask(), member/*=run my task on this member*/);
t = new DitributedTask<String>(new MyTask(), "key"/*run on member owning this key*/);
t = new MultiTask<String>(new MyTask(), members);
es.execute(t);
```

### Advanced Query
```java
import com.hazelcast.core.*;
import com.hazelcast.query.SqlPredicate;
IMap m = hz.getMap("my");
m.addIndex("active", false); //active and age are members of the POJO
m.addIndex("age", true);
Collection<MyClass> c = m.values(new SqlPredicate("active AND age < 30"));
```

### Persistence
    Hazelcast is in-memory by default, but: You can persist, async(=write-behind) or sync(=write-through), or read-through(if get(key) == null -> load!)
```java
import com.hazelcast.core.MapStore;
import com.hazelcast.core.MapLoader;
publi class My implements MapStore, MapLoader {
    public Set loadAllKeys() { }
    public Object load(Object key) { }
    public void store(Object key, Object val) { }
    public void remove(Object key) { }
}
```
## Configuration
```xml
<hazelcast>
    <group><name>d</name><password>p</password><group>
    <properties>
        <property name="hazelcast.initial.min.cluster.size">8</property>
        <property name="hazelcast.icmp.anabled">true</property>
    </properties>
    <network>
        <port auto-increment="true">5701</port>
        <join>
            <multicast...>
            <tcp-ip...>
        </join>
        <interfaces enabled="true">
            <interface>192.168.1.*</interface>
        </interfaces>
    </network>
    <map name="default">
        <backup-count...>
        <max-size>...
        <eviction-policy>LRU
        <map-store>...
        ...
    </map>
</hazelcast>
```
