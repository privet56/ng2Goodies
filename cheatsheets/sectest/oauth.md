# OAuth 2.0 & OpenID Connect
## OAuth 2.0
OAuth 2.0 is often used for delegated authorization; has
1. resource owner
2. client
3. authorization server
4. resource server
5. authorization grant
6. redirect URI
7. access token / refresh token

has
1. back channel (highly secure channel) = your server & your app with the authorization server
2. front channel (less secure) = to/from the browser of the client/user

<img src=oauth.flow.png width="550px" />

#### Implicit flow
Implicit flow uses **only** the front channel!
<img src=oauth.implicitflow.png width="550px" />

Use OAuth2 for authorization for permissions & scopes, **not** for authentication,
because, in OAuth2 there is no standard-way of getting user infos!

## OpenID Connect
**OpenID Connect** is an Extension to OAuth2 for authentication!

OpenID Connect adds:
1. ID token
2. UserInfo endpoint for getting more user infos (you can call it with the access-token)
3. standard set of scopes
4. standardized implementation

OpenID-Connect uses the standard flow, just with an **addtional scope** in the request: openid --> you get back an openid-token too with the access-token!
**idtoken is a JWT (JSON Web Token)**! (decode it with https://jsonwebtoken.io/)

JWT = header + payload(with claims) + signature

<img src=oauth.and.openidc.usecases.png width="450px" />
<img src=oauth.grant.types.png width="450px" />

AppAuth = from Google, lib for authentication in native apps.

## JWT
Use JWT to be **stateless** on the server side! (-> load-balancer has it easier! no sticky sessions or shared-session-cache needed)

1. JWT = base64-encoded JSON of a header & payload & signature
2. header, JSON with
    1. alg (eg. with value HS256)
    2. type: "JWT"
3. payload, JSON, has claims:
    1. iss = issuer (string)
    2. sub = subject (string)
    3. aud = audience (string)
    4. exp = expiration time (number)
    5. nbf = not before
    6. iat = issued at (number)
    7. jti = JWT ID
    8. (name = an optional custom private claim)
    9. (permissions = a private claim (can be an array))
    10. (CRSF = custom claim)
4. signature

```js
var json = parseJSON(base64URLdecode(encodedPayload));
var signaguretoken= hmacSha256(encodedHeader + '.' + encodedPayload, 's3cr3t');//--> now compare this with the signature of the JWT
```
JWT works with any language! -> optimal for microservices!

With certain econding-algorithm (private/public keys), you don't have to share secrets between the microservices.

### JWT - Advanced topics:
1. CSRF with JWT: Add CSRF-token into your payload **and** to the header/cookie(httpOnly)!
    --> server matches if the two CSRF tokens are the same --> Cross-Site-Scripting avoided!
    1. //TODO: is this approach really failsafe?
2. you can use an API-Gateway between browser and app-with-microservices, with two sides:
    1. towards browser, use session ID (more secure because opaque)
    2. towards & between your microservices, use JWT
