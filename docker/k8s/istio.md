# Istio
## Istio Setup:
1. pre-requisite: kubectl & minikube (on local machine) & helm (optional)
2. Download & unzip the latest Release
3. execute:
```sh
kubectl create namespace istio-system
kubectl label namespace default istio-injection=enabled
kubectl apply -f install/kubernetes/helm/helm-service-account.yaml
helm init --service-account tiller
helm install install/kubernetes/helm/istio --name istio 
    --namespace istio-system
    --set gateways.istio-ingressgateway.type=NodePort           # especially advisable on minikube
    --set gateways.istio-egressgateway.type=NodePort            # especially advisable on minikube
    --set sidecarInjectorWebhook.enabled=true
    --set global.mtls.enabled=false                             # mutual TLS
    --set servicegraph.enable=true
    --set ingress.enable=true
    --set tracing.enabled=true
    --set zipkin.enabled=true
    --set grafana.enabled=true
    --set servicegraph.enabled=true
    --set global.proxy.includeIPRanges="10.0.0.1/24"

# kubectl create -f my.yaml       # now, install your app (alternative: helm)
# manual injection, alternative to 'kubectl label namespace default istio-injection=enabled'
# istioctl kube-inject -f my.yaml | kubectl apply -f -

kubectl logs PODID -c istio-proxy   #check if imjection works!, should show listeners|upstream|outbound...
```
4. configure via YAML kind: **Gateway, VirtualService, DestinationRule** for subset routing/mapping
    (eg. for directing different versions of the app, eg. based on **labels, path, header, cookie or hostname**)
    1. subset: entry of the yaml specifies a label: of a kind: Deployment
5. set routing *weights* to adjust load balancing ratios in kind: VirtualService to the destination's
6. implement **Canary** deployments = set *weights* to gradually direct traffic to the new deployment
7. can (de)activate MTLS (=Mutual TLS)
8. can configure communication policy. Example:
```yaml
apiVersion: "authentication.istio.io/v1alpha1"
kind: "Policy"
metadata:
    name: "permissive"
    namespace: "mtls"       # < change here as you need
spec:
    targets:
    - name: hostname        # < change here as you need
    peers:
    - mtls:
        mode: PERMISSIVE    # alternative: STRICT(=doesn't allow nomtls-to-mtls!)
---
apiVersion: "networking.istio.io/v1alpha3"
kind: "DestinationRule"
metadata:
    name: "default"
    namespace: "mtls"
spec:
    host: "*"
    trafficPolicy:
        tls:
            mode: ISTIO_MUTUAL      # disallow mtls-to-nonmtls!     #alternative:DISABLE(=allows mtls-to-nomtls)
```
9. Traces & latencies: check Jaeger UI (port: 16686)
10. Advanced stuff
    1. ***Fault injection*** (for testing purposes: 'time curl -b user=tester ...')
    2. ***Abort injections***
    3. ***Mirroring***
    4. ***Circuit Breaker*** (open source istio tool: fortio)
```yaml
# kind: VirtaulSersvice snippet:
    - match:
        - headers:
            cookie:
                exact: user=tester
        fault:
            delay:                      # fault injection
                percent: 50
                fixedDelay: 5s
            abort:                      # abort injection
                percent: 50
                httpStatus: 500
        mirror:                         # mirror
            host: hostname
            subset: v2
```
