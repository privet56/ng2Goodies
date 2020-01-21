# ACI: Azure Container Instances
Cloud Shell:
```sh
#image source default: dockerhub (alternative: acr from Microsoft)
#-g = group
#--os-type is optional, default is linux
#--cpu, --memory are optional
az container create --name my --image microsoft/iis:nanoserver -g my --ip-address public --os-type Windows --cpu 2 --memory 3.5

az container list -g my -o table

code .   # opens a ui within the cloud shell bash!

#create role assignment
az role assignment create --assignee myclientid --role acrpull --scope myarcid
# build a container image and safe in acr
az acr build --image my/my:v2 --registry myacr --file Dockerfile .
```
1. more complicated infrastructure needed? Use ACS (Azure Container Services with Kubernetes)
1. on the web ui you also can create containers, view details/logs or log into the container, specify environment variables

# ACS: Azure Container Service, AKS: Azure Kubernetes Service
AKS = ACS with Managed Kubernetes
```sh
# register the needed resource provider
az provider register -n Microsoft.ContainerService
# create a resource group
az group create --name my --location eastus
az group list
# create an aks cluster
az aks create --resource-group my --name my --node-count 1 --generate-ssh-keys

az aks list

az aks install-cli  # gets kubectl

#fill kubectl config with this command:
az aks get-credentials --resource-group m --name my

kubectl get cs  # cs = component status
kubectl cluster-info

kubectl create -f my.yaml   # deploy an app from docker image(s) incl LoadBalancer
kubectl get po --watch
kubectl get svc --watch

# without yaml for simple cases:
kubectl run --image=my my   # shortcut without yaml, creates a deployment
kubectl get pods
kubectl expose pod mycont --port=80 --target-port=80 --type=LoadBalancer

az aks scale ...    # scale existing cluster
az aks upgrade ...  # upgrade kubernetes
```
1. on the web ui you also can create AKS clusters
