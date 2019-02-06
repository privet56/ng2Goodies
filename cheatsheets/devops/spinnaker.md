# Spinnaker
Spinnaker is a CD tool from Google/Netflix
1. Spinnaker deploys automatically (to staging) when triggered.
    1. trigger can be jenkins job, webhook...
2. Spinnaker deploys to prod (trigger manually) eg. a la blue-greeen(=red/blue) deployment mode(=strategy) (alternative strategy: highlander)
3. A Spinnaker Application is ~ a k8s cluster.
3. A Spinnaker pipeline has stages (eg. build, deploy, test, publish image, run job, script...)
3. A Spinnaker has also Load Balancer configuration (=k8s type service)
3. A Spinnaker has a Server Group configuration (incl. container-image, load-balancers, replicas, autoscaling, probes(healthcheck)) (k8s = type deployment)
3. supported providers: aws,azure,gce, openstack...
3. storage: Azure Storage, Google Cloud Storage, Minio(~local S3), Redis, S3
3. Community: https://community.spinnaker.io/

## Deployment Pipeline Configuration on the Web UI:
<img src=spinnaker.pipeline.cfg.png width="550px">
<img src=spinnaker.build.png width="550px">

#### Spinnaker Reference - Supported Cloud Providers
1. Azure
2. AWS: ECS
3. GCP: GCE & GAE
4. Kubernetes Legacy (old k8s version)
5. Kubernetes Manifest based - current k8s version

<img src=spinnaker.ref.cloudproviders.png width="550px">

### Install:

> $ kubectl apply -f https://spinnaker.io/downloads/kubernetes/quick-install.yml

(or you can use helm to install)

## Use / Interfaces
1. Web UI
2. CLI: hal (Halyard, a tool for configuring, installing, and updating Spinnaker), e.g. add provider with such a cmd:
    > $ hal config provider kubernetes accound add ACCOUNT [parameters]
3. Spinnaker REST API (see Reference -> API)
