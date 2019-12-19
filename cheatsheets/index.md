<link rel="stylesheet" href="_github-markdown.css">

# Cheatsheets:

### Angular
#### [Angular Server Side Rendering](ngssr/ng.ssr.md)
#### [Advanced Angular (eg. Message Broadcasting, usage of visibilityObserver)](ng/ng.advanced.md)
#### [Angular / Rx](../../../../artiFlow/blob/master/README.md#rx-cheatsheet)
#### [Angular / Animation Material Firebase LazyLoaded Modules](ng/ng.md)
#### [RxJS & NgRx](ng/rxjs.md) & [RxJS](ng/rxjs-2.md)
#### [NgRx](ng/ngrx.md)

### Cloud
#### [Azure](azure/azure.md)
#### [Google Cloud Platform](gcp/gcp.md)
### GWT
#### [SmartGWT](gwt/smartgwt.md)
### Docker / k8s / Helm / Istio
#### [Docker (PowerPoint Presentation, 2017)](./../docker/docker.pptx)
#### [Docker for Windows](./../docker/docker4windows.md)
#### [Kubernetes](./../docker/k8s.md)
#### [Kubernetes on GKE](./../docker/k8s/k8s.md)
#### [CI/CD with Jenkins and Kubernetes](ci_cd_jenkins_kubernetes.md)
#### [Kubernetes on AWS](./../docker/k8s.on.aws.md)
#### [Local Kubernetes Environments with minikube](./../docker/k8slocal.md)
#### [Security in Kubernetes Environment](sectest/sec_k8s.md)
#### [Helm - basics](helm/helm.md)
#### [Helm - advanced (mentioning istio too)](helm/helm4k8s.md)
#### [Istio](helm/istio.md) & [Istio-CodeFresh](helm/istio_helm_canary.md) & [Istio Setup & Config](./../docker/k8s/istio.md)
#### [Multicloud with k8s & Istio & Spinnaker](helm/multicloud.md)
#### [k8s & Rancher](devops/rancher.md)
#### [Spinnaker](devops/spinnaker.md)

#### [Kafka](./kafka/kafka.md)

#### [MS Dynamics CRM](./ms_dynamics/ms_dynamics.md)

### PHP
#### [PHP - HHVM, Hacklang, PHP-FPM](hhvm/hhvm.md)
#### [PHP - Advanced Laravel](php/laravel.md)
#### [PHP - RxPHP](php/rxphp.md)
### Python
#### [Python / Django](../../../../spycy/blob/master/cheatsheet/django.md)
#### [Python / Flask](../../../../spycy/blob/master/cheatsheet/flask.md)

### Qt
#### [Qt .pro/QML](../../../../qBoss/blob/master/qt_cheatsheet.md) (with a chapter for git)
#### [Qt For Android Gotchas (PDF)](../../../../qBoss/blob/master/qt4android_hints/qt4android_hints_for_beginners.pdf)
#### [QtWS18](qt/qtws18.md)

### Security
#### [Penetration Tests](./sectest/pentest.md)
#### [Security Testing](./sectest/sectest.md)
#### [OAuth / OpenID / JWT](./sectest/oauth.md)

#### [Solr](./solr/solr.md)
### Rx
#### [RxJava](./rx/rxjava.md)
#### [RxJava & ReactiveJ](./rx/reactivej.md)
### Scrum
#### [Scrum / Kanban / SAFe](scrum/scrum.md)
### Spark
#### [Spark](spark/spark.md)
#### [Spark with PySpark](spark/spark_pyspark.md)
#### [Spark with Scala](spark/sparkwithscala.md)

#### [Interpersonal Skills](interpersonalskills.md)

#### [Yocto](yocto/yocto.md)
#### [ZooKeeper](zookeeper/zookeeper.md)
#### [Hazelcast](./hazelcast/hazelcast.md)
#### [Redis](./redis/redis.md)
#### [Vert.x](./vertx/vertx.md)

### DevOps
#### [Git / Gitflow](./git/git.md)
#### [GitLab](./devops/gitlab.md)
#### [Varnish](./devops/varnish.md)
#### [PostgreSQL](./devops/postgres.md)
#### 

.

## Diverse:

.

#### How to protect Secret Keys in JavaScript source code?
use jscrambler
1. use jscrambler, with config entry "propertyKeysObfuscation"
2. **Take care**: this hint is not hacker-safe, but often ~good-enough!
3. cfg prop: "name": "propertyKeysObfuscation"
```sh
npm install jscrambler --save-dev 
npm i --save-dev jscrambler-webpack-plugin 
```

#### How to convert PSD to HTML/CSS & pics ?
Use Avocode (desktop app, available for macOS, Win, Linux)
1. Use Avocode (the app is not free) (can also handle Sketch designs with a plugin)
2. After opening the project, you can edit the CSS styles.
3. can export images
4. often, you edit the HTML manually and use the styles & images given by Avocode
5. app shows padding & margin of elements visually

#### How to do (mobile) Cross-Browser testing? 
Use online service of http://www.browserstack.com (not free!)
1. Can do:
    1. live: interactive test & debug of websites in real browsers & mobile devices
    2. Automate
    3. Screenshots & Responsive
2. you can choose from a lot of browser-versions & OSs(Win, macOS, iOS, Android)
3. Plugin for Chrome: 'Local Testing' for non-public websites, eg. from localhost

#### How to speed up Apache?
Use mod_pagespeed: it compresses JS & CSS
```sh
wget https://dl-ssl-google.com/dl/linux/direct/mod-pagespeed-stable_current_amd64.deb
dpkg -i mod-pagespeed*.deb
sudo service apache2 restart
gedit /etc/apache2/mods-available/pagespeed.conf # -> ModPagespeed on|off
gedit /etc/apache2/mods-enabled/pagespeed.conf   # -> /pagespeed_admin = Admin Area!
sudo service apache2 reload
```
/etc/apache2/mods-available/pagespeed.conf
```xml
<IfModule pagespeed_module>
    ModPagespeed on
    ...
```
/etc/apache2/mods-enabled/pagespeed.conf
```xml
<Location /pagespeed_admin>
    Order allow,deny
    Allow from localhost
    Allow from 127.0.0.1
    Allow from 0.0.0.0
    SetHandler pagespeed_admin
</Location>
<Location /pagespeed_global_admin>
    Order allow,deny
    Allow from localhost
    Allow from 127.0.0.1
    Allow from 0.0.0.0
    SetHandler pagespeed_global_admin
</Location>
    ModPagespeedStatisticsLogging on
```

#### SQL: Find book(s) with the minimum average rating
```sql
select avg3.title, avg3.avg_rating
from

(select b.title, avg(r.rating) as avg_rating from ratings r join books b on b.id = r.book_id group by b.title) as avg3

where avg_rating = (select min(avg2.avg_rating2) from (select r2.book_id as id, avg(r2.rating) as avg_rating2 from ratings r2 group by r2.book_id) as avg2);
```

#### Analyze Java Stream
(incomplete)
```java
public class OrdersAnalyzer {

  /**
   * Should return at most three most popular products. Most popular product is the product that have the most occurrences
   * in given orders (ignoring product quantity).
   * If two products have the same popularity, then products should be ordered by name
   *
   * @param orders orders stream
   * @return list with up to three most popular products
   */
  public List<Product> findThreeMostPopularProducts(Stream<Order> orders) {
	  
	  List<Product> ps = new ArrayList<Product>();
    
	 Stream<OrderLine> ols = orders.flatMap((order) -> order.getOrderLines().stream());
	 Map<Product, Integer> acc = new HashMap();
	 ols.forEach(ol -> acc.merge(ol.getProduct(), ol.getQuantity(), Math::addExact));
	 acc.entrySet().stream().sorted(Map.Entry.comparingByValue()).limit(3).forEachOrdered(p -> ps.add(p.getKey()));
	 
	 return ps;
  }

  /**
   * Should return the most valuable customer, that is the customer that has the highest value of all placed orders.
   * If two customers have the same orders value, then any of them should be returned.
   *
   * @param orders orders stream
   * @return Optional of most valuable customer
   */
  public Optional<Customer> findMostValuableCustomer(Stream<Order> orders) {

	  List<Customer> cs = new ArrayList<Customer>();
	  Map<Customer, Integer> acc = new HashMap();
	  orders.forEach(order -> acc.merge(order.getCustomer(), value(order.getCustomer(), order.getOrderLines()), Math::addExact));
	  return acc.entrySet().stream().sorted(Map.Entry.comparingByValue()).map(ac -> ac.getKey()).findFirst();
  }
  private Integer value(Customer c, Set<OrderLine> ols) {
	  
	  int i = ols.stream().mapToInt(ol -> ol.getProduct().getPrice().intValue() * ol.getQuantity()).sum();
	  System.out.println(""+c.getFirstName()+" "+c.getLastName()+" -> val: "+i);
	  return i;
  }
}
```
#### implement js function for which is the call sum(2)(3)(5); is valid!

```js
//solution 1:
function sum(n1)
{
	return function(n2) {
		return function (n3) {
			return n1 + n2 + n3;
		}
	}
}
//alert(sum(2)(3)(4)); //should be 9

//solution 2: ES6
var sum = n1 => n2 => n3 => n1 + n2 + n3;
//alert(sum(2)(3)(4)); //should be 9
```

#### How to combine html files of a directory into one single html file containing all the small file contents?
> copy *.html all.html

TODO: log without überflüssige Calls (lambda!)
