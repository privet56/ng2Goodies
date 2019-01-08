# Apache Kafka
    = Is a messaging system; from LinkedIn
    = Event Ledger, distributed and redundant
    = a distributed commit log
    = uses messaging system semantics
    = Clustering is Core, horizontally distributed across Nodes
    = has durability and ordering guarantees (within a partition)
    = uses Zookeeper to keep track of the state of the cluster & leader
    = can serve real-time processing engines, like Flink (flink has out-of-the-box support for kafka)
### Pieces of Kafka
1. Producers: writes to broker into a topic of a partition
2. Consumers: read from broker, the consumer asks (=pull)
    1. can queries by Start-Offset
    2. consumers can form consumer-groups, so that message consumption is load-balanced across all consumers in the group
3. Events
4. Topics, its replication factor can be specified
5. Partition (they are replicated); ordering is guaranteed only for a partition
6. Broker = a Node in the cluster(= leader + followers)
7. Connectors
8. Cluster = sum of Brokers and a Zookeeper. Producers push, consumers pull
9. Zookeeper is used for service discovery (=broker node discovery)
### Use Cases
    ETL(Extract, Transform, Load)/CDC(=Change Data Capture)
    Data Pipelines (producers feed in, consumers use it)
    Big Data Ingest
### CLI
```sh
# these .sh files are provided in kafka download
bin/zookeeper-server-start.sh config/zookeeper.properties
bin/kafka-server-start.sh config/server.properties

bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 partitions 1 --topic topicname

# this producer allows to write to console the msgs to be published
bin/kafka-console-producer.sh --broker-list localhost:9092 --topic topicname
> {"k1":"val","k2":"val"}

# this consumer writes published msgs to console
kafka-console-consumer --bootstrap-server localhost:9092 --topic topicname --from-beginning

```
### Delivery Guarantees
#### Producer
1. Async (no guarantee)
2. committed to leader
3. committed to leader and quorum(=majority of the cluster) (slowest & most secure)
#### Consumer
1. at-least-once delivery (default) (redelivery can occur)
2. at-most-once delivery
3. effectively-once delivery
4. exactly once (maybe)

## Records  = Events = Messages
1. Key + Value + Timestamp
2. Immutable
3. Append Only
4. persisted to disk by kafka (->durability)
## Advanced stuff
1. Heroku Kafka = kafka in the cloud, incl Zookeeper
    1. (you have to use SSL on Heroku)
2. Log Compaction = ignore duplicate events(=has the same key) when writing to disk
3. Disk not heap = use disk and spare heap for caching
4. pagecache to socket = move data from disk to network fast (on nix*)
5. balanced partitions & leaders (rebalances leader if necessary, automatic rebalancing)
6. producer and consumer quotas
7. use akka streams (=reactive Streams) -> reactive Kafka (https://github.com/akka/reactive-kafka)
    1. source/sink stream programming
    2. can backpressure in case of spikes
## Clients
1. JVM
2. clients consume pull based
3. kafka needs a 
    1. Serializer to write records, for key and for value
    2. Deserializer to read records
3. Serializer: json(=large) or avro or protobuf etc

```java
//producer
class Producer {
    public void send(ProducerData<K,V> producerData);
}
//consumer
class SimpleConsumer {
    public ByteBufferMessageSet fetch(FetchRequest request);
    public long[] getOffsetsBefore(String topic, int partition, long...
}
interface ConsumerConnector {
    public Map<String, List<KafkaStream>> createmessageStreams(Map<String, ...
}
```
### Rective API:
    Example: https://github.com/jamesward/koober (in scala)
```scala
val src = Source.repeat("12");
val snk = Sink.foreach(println)
val flw = source to sink
flow.run()
```

<img src="reactive-kafka.png" width="550px">

### Spring-Kafka
    Spring-Boot supports Spring-Kafka:
```xml
<dependency>
    <groupId>org.springframework.kafka</groupId>
    <artifactid>spring-kafka</artifactid>
 </dependency>
<dependency><!-- add this if you use json serialization (or avro, or protobuf...) -->
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactid>jackson-databind</artifactid>
    <version>2.6.7</version>
 </dependency> 
```
```java
public class MyProducer {
    @Autowired
    KafkaTemplate<String, Model> kafkaTemplate; //'Model' is a POJO
    public void f()
    {
        kafkaTemplate.send("topicname", new Model("val")); //=publish message!
    }
}
@EnableKafka //only needed for Consumer
@Configuration
public class KafkaCfg {
//cfg for a producer
    @Bean
    public ProducerFactory<String, Model> produerFactory() {
        Map<String, Object> cfg = new HashMap<>();
        cfg.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "127.0.0.1:9092");
        cfg.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        cfg.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, JsonSerializer.class);

        return new DefaultKafkaProducerFactory(cfg);
    }
    @Bean
    public Kafkatemplate<String, Model> kafkatemplate() {
        return new KafkaTemplate<String, Model>(producerFactory());
    }
//cfg for a consumer
//  string value
    @Bean
    public ConsumerFactory<String, String> consumerFactory() {
        Map<String, Object> cfg = new HashMap<>();
        cfg.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "127.0.0.1:9092");
        cfg.put(ProducerConfig.GROUP_ID_CONFIG, "group_id");
        cfg.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        cfg.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, StringSerializer.class);

        return new DefaultKafkaConsumerFactory<>(cfg);
    }
    @Bean
    public ConcurrentKafkaListenerContainerFactory<String, String> kafkaListenerContainerFactor() {
        ConcurrentKafkaListenerContainerFactory<String, String> factory = new ConcurrentKafkaListenerContainerFactory();
        factory.setConsumerFactory(consumerFactory());
        returen factory;
    }
//  model value
    @Bean
    public ConsumerFactory<String, Model> modelConsumerFactory() {
        Map<String, Object> cfg = new HashMap<>();
        cfg.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "127.0.0.1:9092");
        cfg.put(ProducerConfig.GROUP_ID_CONFIG, "group_id_json");
        cfg.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        cfg.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, JsonSerializer.class);

        return new DefaultKafkaConsumerFactory<>(cfg, new StringDeserializer(), new JsonDeserializer<>(Model.class));
    }
    @Bean
    public ConcurrentKafkaListenerContainerFactory<String, Model> modelKafkaListenerContainerFactor() {
        ConcurrentKafkaListenerContainerFactory<String, Model> factory = new ConcurrentKafkaListenerContainerFactory();
        factory.setConsumerFactory(modelConsumerFactory());
        returen factory;
    }
}
@Service
public class MyConsumer {
    @KafkaListener(topics="topicname", group="group_id")
    public void consumeStringMsg(String msg) {
        //handle msg
    }
    @KafkaListener(topics="topicname", group="group_id_json", containerFactory="modelKafkaListenerFactory")
    public void consumeJsonMsg(Model model) {
        //handle msg
    }
}
```
