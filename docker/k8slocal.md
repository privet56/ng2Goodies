# Local Kubernetes Environments with minikube
## To run Kubernetes on your laptop, you'll need to install:
1. kubectl
2. minikube
3. docker
## Install kubectl
    See: https://kubernetes.io/docs/tasks/tools/install-kubectl/
```sh
# linux
curl -LO https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl && chmod +x kubectl && sudo mv kubectl /usr/local/bin/
# macOS
curl -LO https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/darwin/amd64/kubectl && chmod +x kubectl && sudo mv kubectl /usr/local/bin/
```
### To verify kubectl availability, try running:
```sh
kubectl help
```
## Install minikube
    See https://github.com/kubernetes/minikube/releases
```sh
# linux
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64 && chmod +x minikube && sudo mv minikube /usr/local/bin/
# macOS
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-darwin-amd64 && chmod +x minikube && sudo mv minikube /usr/local/bin/
```
### Optionally, customize your cluster's memory or cpu allocation:
```sh
minikube config set memory 4096
minikube config set cpus 2
```
### to verify minikube availability:
```sh
minikube version
```

## Minikube Basics
```sh
minikube start  # run k8s locally
minikube stop   # halt VM
minikube delete
```
### Minikube Gotchas
1. Minikube requires an OS virtualization back-end
2. Most OSes include some support for virtualization
3. You can use the --vm-driver flag to select a specific virt provider:
```sh
 minikube start --vm-driver=virtualbox
```
4. Check the project README for more information about supported virtualization plugins: https://github.com/kubernetes/minikube/blob/master/docs/drivers.md

## Docker install:
Use your package manager, or download a release from Docker
```sh
brew cask install docker
dnf install docker
apt-get install docker
docker version  # To verify docker availability
```
### k8s
Verify that your local Kubernetes environment is ready by running:
```sh
kubectl version
```
##  kubectl
### definitions
1. Node = host machine (physical or virtual) where containerized processes run. Node activity is managed via one or more Master instances.
2. Pod =  group of one or more co-located containers. Pods represent your minimum increment of scale.
3. Service = (svc) establish a single endpoint for a collection of replicated pods, distributing inbound traffic based on label selectors
In our K8s modeling language they represent a load balancer. Their implementation often varies per cloud provider
4. Deployment = specify container runtime requirements (in terms of pods)
5. replicaset = provides replication and lifecycle management for a specific image release
6. Kubelet = Runs on each node, listens to the API for new items with a matching NodeName
7. Kubernetes Scheduler = Assigns workloads to Node machines
### Example Calls:
```sh
# Create a pod and a service. Verify that the service is responding:
kubectl run myapp --image=quay.io/ryanj/metrics-k8s \
--expose --port=2015 --service-overrides='{ "spec": { "type": "NodePort" } }'
minikube service myapp
# ssh into minikube, kill the control plane:
minikube ssh
ps aux | grep "kube-apiserver"
sudo killall kube-apiserver
logout
# Use kubectl to list pods:
kubectl get pods

```
