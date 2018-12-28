# Helm for Kubernetes
	Kubernetes = k8s = deployments(in pods) & services & ingress
	A Helm chart defines a group of manifest files
	Helm = package manager for kubernetes
	packages called charts stored in one or more repositories
	Charts contain templatized k8s config
	Setup client configuration and install server-side tiller:
		$ helm init		# possibly with the wait param
	Check if tiller is available:
		$ kubectl rollout status deployment -n kube-system tiller-deploy

## Structure of a Chart:
	myapp/
		Chart.yaml
		templates/
			deployment.yaml			# manifest templates
			service.yaml
			ingress.yaml
		values.yaml
### Usage:
```sh
helm install myapp
helm list				# lists deployed deployments
```
### Chart.yaml
```yml
name: my app
version: 1.0.0
description: my app
maintainers:
	- name: me
	  twitter: me
```
### deployment.yaml
```yml
apiVersion: extensions/v1beta1
kind: Deployment
metadata:
	name: nginx
spec:
	replicas: 3									# this is hardcoded :-(
	replicas: {{.Values.scale}}					# this is helm!
	template:
		metadata:
			labels:
				app: nginx
		spec:
			containers:
			- name: nginx
			  image: nginx:1.3					# this is hardcoded :-(
			  image: nginx:{{.Values.tag}}		# this is helm!
			  ports:
			  - containerPort: 80
```
### service.yaml
```yml
kind: service
apiVersion: v1
metadata:
	name: nginxservice
spec:
	selector:
		app: nginx
	ports:
	- name: main
	  protocol: TCP
	  port: 80
	  targetPort: 80
```
### ingress.yaml
```yml
apiVersion: extensions/v1beta1
kind: Ingress
metadata:
	name: nginxingress
	annotations:
		http.port: "443"
spec:
	backend:
		serviceName: nginxservice
		servicePort: 80
```
### values.yaml
```yml
scale: 3
tag: "1.3"
```
### fire up helm:
mac install:
```sh
brew cask install minikube
minikube start
minikube addons enable ingress
minikube addons enable registry		# uses docker-registry inside of the minikube cluster
brew install kubectl
brew install kubernetes-helm
```
```sh
helm install myapp/						# outputs deployment-name too, use --name to set your own name
helm delete {deployment-name}
helm upgrade --set scale=3,tag="1.3" {deployment-name} myapp/
helm rollback {deployment-name} 1
# search kubeapps.com	# uses monocular = helm chart repository incl. UI = open source project
helm search jenkins
# creates deployment, services, secret, config maps, persisten volume claim
# 'stable' is the repo name
helm install --name cd stable/jenkins
# or
helm install --name cd -f override.yaml stable/jenkins

helm status
# access the jenkins UI:
minikube service cd-jenkins

```
### helm uses the Kubernetes plugin for Jenkins
	Spins up Jenkins slave as Kubernetes pod on demand
	Pod template defines containers that should exist in pod
		JNLP agent is always one of them
		Enables re-use of existing Docker images (e.g maven, golang or docker)
	Template can define other configuration for the pod/containters
		Environment variables
		Mount from secret, config map or volume
