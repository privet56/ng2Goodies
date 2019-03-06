# gke & k8s
## k8s
1. offers (1) autohealing &  (2) (auto-)scaling &  (3) load-balancing & (4) isolation
2. is a container-orchestrator, maintaining container-clusters
3. is multi-cloud capable (aws,gcp-gke,azure), but especially fine for gke
4. has 1-n master node and worker nodes. master is managed by GKE
5. use YAML in general or the gcloud interface on GKE
6. has **Services** provide stable (non-ephemeral) IP addresses for external connections and load-balancing
    1. set of pods selected via label selector
7. has **Volumes** for durable storage (=persistent volume) (supported: awsElesticBlockStore, azureDisk, azureFile, gcePersistentDisk)
    1. static provisioning: for pre-created volumes
    2. dynamic provisioning: via PersistentVolumeClaim

8. has **Load Balancers**
    1. with static IP &
    2. with forwarding rules to funnel traffic &
    3. with health-checks
9. has **Ingress** = rules that allow inbound connections to reach (multiple) cluster services.
    1. with externally reachable URLs
    2. load-balancing
    3. SSL termination
    4. name-based virtual hosting
10. has StatefulSets and DaemonSets
    1. **StatefulSets** is similar to ReplicaSet but Pods are unique with stable host name and are associated with persistent folume. Useful for ***stateful apps***, like kafka, mysql, redis, zookeeper...
    2. **DamonSet** for long-running apps which run in background (without user intervention), eg. loc-collection, node-monitoring (they cannot be autoscaled)
11. has **Horizontal Pod Autoscaler (HPA)** = autoscaling + autohealing
    1. autoscaling based on CPU utilization or requests-per-second
    2. ReplicaSet's or Deployment's can be autoscaled (but, eg. DaemonSet's cannot be autoscaled)
    3. specify cool-down-period to avoid frequent up/down-scaling
12. has **Binary Authorization** = a deploy-time security control that ensures only trusted container images are deployed on GKE (is an optional feature)
    1. requires images to be signed by trusted authorities
    2. signing must occur during development
    3. integrates with GCR vulnerability scanning
    4. Setup:
        1. configure policy (specify which images are allowed to be deployed here)
        2. set up attestor (=entity that signs off, human or system with public key)
        3. sign container image (=create attestation, a digitally signed record with full path to image)
        4. deploy container image, as usual

## GCP GKE Web Console
1. https://console.cloud.google.com/ -> Create a project
2. Choose **Kubernetes Engine** -> [create cluster] ->
    1. select a zone|region
    2. specify number of nodes & machine type(CPU, memory), image type, disks
    3. check enable autoscaling (with min & max number or nodes)
    4. advanced option: enable Stackdriver monitoring & logging
3. Choose Workloads -> [create deployment] ->
    1. specify container image (from dockerhub or GCR (google container registry))
    2. add|set environment variables
4. Choose Expose deployment (as a Service) -> select port and service-type. Service-Types:
    1. clusterIP = exposes the service on an internal IP in the cluster
    2. NodePort = exposes the service on the same port of each selected node
    3. Load-Balancer = creates a load-balancer with external IP
5. Finished (without a single YAML line or kubectl command!)! Your app is now externally available! GKE automatically created VPC, firewall rules (incl. SSH access)
6. you can see the stackdriver logs/montoring/metrics inside of the web ui
## glcoud
gcloud is a GCP-GKE command line utility as an alternative to the web based ui (can be used within the browser (cloud shell))
```sh
gcloud config set project myproject
gcloud config set compute/region us-central1
gcould components update
# create cluster: - verion 1
gcould container clusters create mycluster --num-nodes 2 --region us-central1 --enable-autorepair \
    --disk-size=15GB --disk-type=pd-standard --enable-autoscaling --min-nodes 1 --max-nodes 10
# create - verion 2: single-zone cluster:(without stackdriver log|monitoring)
gcould container clusters create mycluster --zone us-central1-a --preemptive --machine-type n1-standard-1 --no-enable-cloud-monitoring --no-enable-cloud-logging

# update cluster settings (here: enable logging)
gcloud container clusters update mycluster --zone us-central1-a --logging-service="logging.googleapis.com"

gcould compute machine-types list
gcould container clusters describe mycluster --zone us-central-a

# updates kubeconfig for kubectl usage
gcloud beta container clusters get-credentials mycluster --region us-central1 --project myproject
gcloud container node-pools list --cluster mycluster --region us-central1
gcloud container node-pools create mypool --num-nodes=2 --cluster mycluster --region us-central1
gcloud beta container clusters resize mycluster --region us-central1 --node-pool mypool --size 4

# do span multiple zones
gcloud container clusters update mycluster --zone us-central1-a --node-locations us-central1-a,us-central1-b
# del a cluster
gcloud container clusters delete mycluster --region us-central1

gcloud auth login
# forwarding-rules direct traffic from LoadBalancer to backend instances
gcloud compute forwarding-rules list
```
### kubectl within the Cloud Shell
```sh
glcoud components install kubectl
# can use kubectl:within cloud shell:
cat ~/.kube/config              # kubeconfig, contains auth info too & current-context
kubectl config current-context  # lists default cluster
kubectl cluster-info            # shows current default cluster
kubectl config view
kubectl config get-value project    # outputs current project
kubectl run nginx --image=nginx --replicas=2    # creates a deployment in the current cluster
kubectl get pods -owide         # list running pods
kubectl get nodes
kubectl expose deployment nginx --port=80 --target-port=80 --type=LoadBalancer
kubectl get service nginx       # lists also the EXTERNAL-IP
kubectl delete service nginx
kubectl delete deployment nginx
# create a deployment & service
kubectl run nginx --image=k8s.gcr.io/nginx --requests=cpu=200m --expose --port=80
kubectl autoscale deployment nginx -cpu-percent=50 --min=1 --max=10
kubectl get hpa # describe state of the HPA
kubectl run -i --tty load-generator --image=busybox /bin/sh # > next line is inside of the running container!
    / $ while true; do wget -q -O- http://nginx.default.svc.cluster.local; done
```
### Deploy a custom docker image
```sh
# docker is preinstalled on Cloud Shell
docker build -t gcr.io/projectname/myname:v1 .
gcloud auth configure-docker
docker push gcr.io/projectname/myname:v1
# you can find the new image in GCP->Container Registry incl sha256 id
kubectl run myname --image gcr.io/projectname/imagename@sha256:longlongstring --replicas 3
kubectl expose deployment myname --port=80 --target-port=80 --type=LoadBalancer
kubectl get service myname -> look EXTERNAL-IP
kubectl create -f ingress.yaml  # create this in the Cloud Shell File Editor
kubectl get ingress myingress --watch
kubectl describe ingress myingress
kubectl delete -f ingress.yaml  # cleanup
kubectl get pvc     # lists Volume Claims
kubectl create secret generic my --from-literal=password=s3cr3t
kubectl get event       # lists events occured recently
```
#### Ingress.yaml
Ingress = rules to allow inbound connections to reach cluster services, sits in front of the LoadBalancer
```yaml
apiVersion: extensions/v1beta1
kind: Ingress
metadata:
    name: myingress
spec:
    backend:
        serviceName: myservice
        servicePort: 80
```
#### VolumeClaim.yaml
```yaml
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
    name: myvc
spec:
    accessMode:
    - ReadWriteOnce
    resources:
        requests:
            storage: 200Gi
```
#### Deployment.yaml referencing Volume Claim
```yaml
apiVersion: extensions/v1beta1
kind: Deployment
metadata:
    name: my
    labels:
        app: my
spec:
    replicas: 1
    selector:
        matchLabels:
            app: my
    template:
        metadata:
            labels:
                app: my
        spec:
            containers:
            - image: my
              name: my
              env:
                - name: DB_HOST
                  value: mysql:3306         # reference to an internal service!
                - name: MY
                  valueFrom:
                    secretKeyRef:
                        my: my
                        key: password       # -> kubectl create secret generic my --from-literal=password=s3cr3t
              ports:
                - containerPort: 3306
                  name: myp
              volumeMounts:
                - name: my-persistent-storage
                  mountPath: /var/lib/my
            volumes:
                - name: my-persistent-storage
                  persistentVolumeClaim:
                    claimName: mypvc
```
#### Service.yaml
A service for **internal usage** (here: MySQL):
```yaml
apiVersion: v1
kind: Service
metadata:
    name: mysql
    labels:
        app: mysql
spec:
    type: ClusterIP # exposes for internal usage
    ports:
        - port: 3306
    selector:
        app: mysql
```
A service to expose towards **outside** (will get an EXTERNAL-IP):
```yaml
apiVersion: v1
kind: Service
metadata:
    name: wordpress
    labels:
        app: wordpress
spec:
    type: LoadBalancer
    ports:
        - port: 3306
          targetPort: 80
          protocol: TCP
    selector:
        app: wordpress
```
#### Binary Authorization
```sh
gcloud services enable container.googleapis.com
gcloud services enable binaryauthorization.googleapis.com
gcloud auth configure-docker --quiet
gcloud beta container clusters update mycluster --enable-binauthz --zone us-central1-a
gcloud beta container binauthz policy import mypolicy.yaml
kubectl get events # if something went wrong, look here
# submitthe note to Container analysis API
curl -vvv -X POST -H "Content-Type: application/json" -H "Authorization: Bearer $(glcoud auth print-access-token)" --data-binary @./create_note_request.json "https://containeranalysis.googleapis.com/v1alpha1/projects/my/notes/?noteId=noteid"

curl -vvv -X POST -H "Content-Type: application/json" -H "Authorization: Bearer $(glcoud auth print-access-token)" --data-binary @./iam_request.json "https://containeranalysis.googleapis.com/v1alpha1/projects/my/notes/?noteId=noteid:setIamPolicy"

gcloud beta container binauthz attestors create myattestorid --attestation-authority-note=noteid --attestation-authority-note-project=projectid

sudo apt-get install rng-tools -y   # rng = random number generator
sudo rngd -r /dev/urandom
gpg --batch --gen-key <(            # generate a key apir
    cat <<- EOF
        key-Type: RSA
        Key-Length: 2048
        Name-Real: Signing Role
        Name-Email: my@me.com
        %commit
EOF
)
gpg --armor --export my@me.com > ./public.pgp
gcloud beta container binauthz attestors public-keys add --attestor=myattestorid --public-key-file=./public.pgp
gcloud beta container binauthz attestors list
gcloud beta container binauthz create-signature-payload --artifact-url=mycontainerpath@containerimagedigest > ./payload.json
gpg --local-user my@me.com --armor --output ./signature.pgp --sign ./payload.json
KEY_FINGERPRINT=$(gpg --list-keys my@me.com | sed -n '2p')
gcloud beta container binauthz attestations create --artifact-url=mycontainerpath@containerimagedigest --attestor=myattestorid --attestor-project=projectid --signature-file=./signature.pgp --pgp-key-fingerprint="$KEY_FINGERPRINT"
gcloud beta container binauthz policy import mypolicy.yaml # with requireAttestationsBy
kubectl run my --my --image "mycontainerpath@containerimagedigest"

```
mypolicy.yaml
```yaml
admissionWhitelistPatterns:
- namedPattern: gcr.io/google-containers/*
- namedPattern: k8s.gcr.io/*
defaultAdmissionRule:
    evaluationMode: ALWAYS_DENY
    enforcementMode: ENFORCED_BLOCK_AND_AUDIT_LOG
    requireAttestationsBy:
    - projects/projectid/attestors/attestorid
```
create_note_request.json
```json
{
    "name":"project/my/notes/noteid",
    "attestation_authority": {
        "hint": {
            "human_readable_name": "this note represents an attestation authority"
        }
    }
}
```
iam_request.json - give binary authorization the permissions to view the note in the Container Analysis API - BinAuth can query the API to verify that images have been attested
```js
{
    'resource':'projects/projectid/notes/noteid',
    'policy': {
        'bindings':[
            {
                'role':'roles/containeranalysis.notes/occurences/viewer',
                'members':[ 'serviceAccount:somemail']
            }
        ]
    }
}
```
### Monitoring GKE Clusters
Tools: Stackdriver (in GKE only) & Prometheus (also outside of GKE). 
Prometheus can expose metrics to Stackdriver.

Choose Stackdriver Monitoring on the Web UI -> you can see some metrics, logs, charts, pod-details

You can set up ***Alert***'s, incl Conditions (eg. CPU utilization)... target: eg. Email.

You need an RBAC YAML (kind: Namespace, kind: ClusterRole) to connect Prometheus metrics to Stackdriver... 
```sh
curl -sSO "https://storage.googleapis.com/stackdriver-prometheus-documentation/rbac-setup.yml"
kubectl apply -f rbac-setup.yml --as=admin --as-group=system:masters
curl -sSO "https://storage.googleapis.com/stackdriver-prometheus-documentation/prometheus-service.yml"
# edit yml file, set projectid, clustername, location
kubectl apply -f prometheus-service.yml
kubectl get deployment,service -n stackdriver
```
Look in Stackdriver -> Resources -> Metrics Explorer -> Find by Kubernete Container & external/prometheus/...

