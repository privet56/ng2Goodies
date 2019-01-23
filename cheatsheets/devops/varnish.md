# Varnish
1. Is an HTTP cache, can be used on PHP
2. uses HTTP headers, eg.
    1. request headers
        1. Accept: */*
        2. Accept-Encoding: gzip, deflate
        3. User-Agent: Chrome/52
        4. Cookie: ...
        5. Host: bla.be
    2. response headers
        1. Cache-Control: private, max-age=0
        2. Content-Encoding: gzip
        3. Date
3. VCL = Varnish configuration language
4. is a system daemon on Linux
5. is a reverse proxy & load balancer
6. VMOD = binary extension, ~plugin
7. can security (httpoxy, slowloris)

## Workflow
1. client -> vcl_recv() -> is-in-cache -> vcl_deliver()
1. client -> vcl_recv() -> not-in-cache -> vcl_backend_fetch() -> your php webapp -> vcl_backend_response() -> vcl_deliver()

## VCL
> $ cat /etc/varnish/default.vcl
```python
vcl 4.0;
sub vcl_recv() { }
sub vcl_backend_response { }
sub vcl_backend_fetch { }
sub vcl_deliver { }
```
```python
sub vcl_recv {
    # Only cache get or head requests
    if(req.method !="GET" && req.method != "HEAD") {
        return (pass);
    }

    if(req.http.host ~ "^(www\.)?domain\.tld$" || req.http.host ~ "test") {
        set req.backend = specific_backend; #  route to a different server!
        return (pass);
    }

    if(req.url ~ "^[^?]*\.(css|gif)(\?.*)?$") {
        unset req.http.Cookie;
        return (lookup);
    }

    # remove google analytics cookies, as not needed on the server
    set req.http.Cookie = regsuball(req.http.Cookie, "__utm.=[^;]+(; )?", "");
    set req.http.Cookie = regsuball(req.http.Cookie, "_ga=[^;]+(; )?", "");

    # you can lie to your server-side app about the client!
    set req.http.host = "google.com"; 
    set req.http.User-Agent = "IE5";
}

sub vcl_backend_response {

    if(beresp.status == 500 || beresp.status == 502 || beresp.status == 503) {
        return (abandon);   # error wont be cached!
    }

    if(bereq.url ~ "^[^?]*\.(css|gif)(\?.*)?$") {
        unset bereq.http.Set-Cookie; # case-insensitive headers
        return (deliver);
    }

    # allow stale content, in case the backend goes down
    # better to serve old content than no content at all
    set beresp.grace = 2h; # varnish will keep objects for 2 hours beyond their TTL

    set beresp.ttl = 600s;
    set beresp.status = 123; # you can lie to the client
    unset beresp.http.set-cookie;  # is case-insensitive!
}

sub vcl_deliver {
    if(obj.hits > 0) {
        set resp.http.X-Cache = "HIT";
    } else {
        set resp.http.X-Cache = "MISS";
    }
    set resp.http.X-Cache-Hits = obj.hits;
    unset resp.http.X-Powered-By;
    unset resp.http.Server;
}
# determining hash keys
sub vcl_hash {
    hash_data(req.url);
    hash_data(req.http.host);
    hash_data(req.http.Cookie); # session-id is inside the cookie

    if(req.http.Authorization) {
        hash_data(req.http.Authorization);
    }
}
import cookie; # is a VMOD
sub vcl_recv {
    # sort query args
    set req.url = std.querysort(req.url);
    # remove GA tags
    set req.url = regsuball(req.url, "(utm_source|utm_medium)=(...)", "");

    if(req.http.host == "domain.tld") {
        return (synth(720, "http://www.domain.tld"));
    }

#import cookie;
    # use libvmod-cookie
    cookie.parse(req.http.cookie);
    # filter all execpt these
    cookie.filter_except("custom_cookie,custom_cookie2");
    set req.http.cookie = cookie.get_string();
}
sub vcl_synth {
    if(resp.status == 720) {
        set resp.http.Location = resp.reason;
        set resp.status = 301;
        return (deliver);
    }
}
```
## Flushing the cache
1. purge request
2. varnishadm: BANs
3. restart varnish
### Purge
```python
acl purge {
    "localhost";
    "192.168.55.0"/24;
}
sub vcl_recv {
    if(req.method == "PURGE") {
        if(!client.ip ~ purge) {
            return (synth(405, "not allowed"));
        }
        return (purge);
    }
}
```
> $ curl -X PURGE -H "Host: domain.tld" http://31.193.180.217/bla/
### Ban
```sh
> $ varnishadm -S /etc/varnish/secret "ban req.http.host ~ (www.)?domain.tld"
# connect to varnish on a different host
> $ varnishadm -S /etc/varnish/secret -T 31.193.180.217:6082 "ban req.http.host ~ www.domain.tld && req.url ~ .css"
```
### ESI: Edge side includes
1. cache parts of a page
2. works like html/php includes
3. can have different cache policies per fragment
```html
<div>
    <esi:include src="/partial/navi">
</div>
```
### How long to cache?
Optimal: set Cache-Control headers in your app.
### Grace Mode
Varnish overrides TTL header
```python
sub vcl_backend_response {

    set beresp.ttl = 10s; # = cache lifetime
    
    set beresp.grace = 20m;
}
```