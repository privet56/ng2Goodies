# ZooKeeper
    used most in hadoop
    use to coordinate distributed apps
    is distributed, reliable, fast
    guarantees consistency (atomicity, reliability, timeliness)
    Used by:
1. HBase (for master elections...)
2. Hadoop & MapReduce (IBM Big Insights)
3. Flume (for configuration)
4. Kafka
5. Storm
## Zookeeper = coordination service for ...
1. configuration (share config info across all nodes)
2. naming service (find a machine in a cluster by name)
3. provides distributed synchronization (locks, barriers, queues)
4. provides group services (eg. leader election)
### Architecture, a Zookeeper Service:
1. has leader
2. has followers (optional, if you need reliability & high-availability & resilience)
3. serving the connected clients (zookeeper creates as session for the client (until timeout, incl heartbeats & failover))
### Namespaces
Distributed processes coordinate through shared hierarchical namespaces, these are organized  hierarchically, like a file system).
A namespace consists of data registers:
1. called znodes
2. similar to dirs & files
3. node holds data, children, or both
You can assign ACLs to the znodes.
### Operations
1. create: creates a znode
2. delete
3. exists
4. getACL, setACL
5. getChildren
6. getData, setData
7. sync
8. getState: states: connecting, connected, closed
### CLI
1. ls /
2. create /myznode
3. delete
4. set /myznode 'mydata'
5. get
#### Arguments:
1. -s (=sequencial)
2. -e (=ephemeral), eg: $ create -e /myznode
#### Watches:
A watch notifies apps of a change. You can watch for
1. notify of changes in znodes
2. notify of changes in zookeeper states

examples: nodeCreated, nodeDeleted, nodeDataChanged, nodeChildrenChanged
## APIS: java & C
APIs re in java & c, (bindings in c#, python, ruby...)

java:
1. org.apache.zookeeper
2. org.apache.zookeeper.data
3. two threads are spawned when a zookeeper object is created
    1. IO thread
    2. event thread

C
1. single-threaded and multi-threaded lib: zookeeper_st, zookeeper_mt

### Java API
1. ZooKeeper(string connectionString, int sessionTimeout, Watcher watcher)
2. void create(String path, byte[] data, List<ACL> acl, CreateMode createmode)
3. Stat exists(String path, boolean watch)
4. List<String> getChildren(String path, boolean watch)
5. byte[] getData   // get data of a znode
6. setData(String path, byte[] data, int version)
#### Exceptions
1. InterruptedException //if operation canceled
2. KeeperException //state, recoverable, unrecoverable exceptions
    1. KeeperException.NoNodeException
    2. KeeperException.SessionExpiredException

## ACL
Access Control List (=ACL), not recursive!
1. Permissions:
    1. CREATE: can create znode
    2. READ: getChildren/getData
    3. WRITE: setData
    4. DELETE: del znode
    5. ADMIN: setACL
2. built-in ACL schemes: world, auth, digest, ip
    1. example: ip:19.23.0.0/16, READ
3. Usage:
    1. ACL my = new Id(Perms.READ, new Id("ip","10.0.1"));
4. predefined ACLs and Ids in java under the ZooDefs.Ids class
    1. OPEN_ACL_UNSAFE, grants all permissions except admin to everyone
    2. READ_ACL_UNSAFE, gives the world the ability to read
    3. ANYONE_ID_UNSAFE, the Id represents anyone
### Authentication
1. Authentication is pluggable. interface: AuthenticationProvider
2. built-in auth plugins: id, digest
3. add auth plugin in zookeeper.authProvider:
    1. authProvider.1=com.my.MyAuth1
### Advanced Stuff
1. Apache Curator Framework & Client: is a wrapper for ZooKeeper:
    1. client.create().forPath("/my/path", myData)
#### Recipes
Recipes are ordered functions implementing the ZooKeeper Service. Can be used for specific apps requiring ZooKeeper.

1. Out-of-the-box apps:
    1. name service
    2. configuration
    3. group membership
2. Additionals Recipes that can be implemented using ZooKeeper
    1. barriers
    2. queues
    3. locks
    4. two-phase-commit
    5. leader-election (eg. in HBase)

The Curator Framework implements all these recipes except of two-phase-commit.

### ZooKeeper Atomic Broadcast (Zab)
Broadcast protocol used to propagate state changes from the leader.
Used primarily for Leader Election.

(Alternative: paxos)

## Config
1. autopurge.snapRetainCount
2. autopurge.purgeInterval
3. Monitoring: JMX
4. Logging: log4j (in the /conf dir)
5. config params
    1. clientPort
    2. dataDir
    3. tickTime
