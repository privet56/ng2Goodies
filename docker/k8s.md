# k8s = kubernetes
	for container orchestration
	incl. define relationships between containers, how they (auto-)scale
	Alternatives: Docker Swarm, AWS ECS, Mesos

	Container: Docker is dominant

	Kubernetes is a container orchestration standard, cloud-agnostic

### Where/How to run?
	Training: minikube (local version of k8s)
	Development: minikube, dev cluster on a cloud provider
	Deployment: cloud provider or bare metal

## on AWS:
	Do it yourself on EC2's
	ECS has its own proprietary orchestration system, not k8s compatible
	use kops, a tool for production grade k8s installation, upgrade management

## on GCP (Google Cloud Platform)
	GKE (Google Container Engine) speaks k8s, automates cluster setup, maintenance, scaling, healthcheck
	or
	use kops for manual configuration of a k8s cluster on GCE VMs (Google Compute Engine)

## Definitions:
	Deployment = definition of an application
	Deployment = collection of resources & references & exposed ports
		Deployment-Description: in YAML
	Pod = group of instances of a container in a deployment
		= 1+ containers with shared IP/resources
	Service = endpoint that exports a port to the outside world
			= Grouping of pods (acting as one) has stable virtual IP and DNS name
	Label = Key-Value pairs associated with k8s ojbects (eg. app=appname, env=prod, version=1)
	Master = the k8s installation, has APi & etcd & scheduler & controllers

## kubectl & minikube
	runs k8s locally, but does not support load balancers, persistent volumes, ingress
	requires virtualization & hypervisor (kvm, Virtualbox(on linux) or VMWare(macOS or linux))
	install kubectl & minikube
	$ kubectl
	$ kubectl.exe on windows
	download url: see in the docs:
		https://kubernetes.io/docs/tasks/tools/install-kubectl/
		https://github.com/kubernetes/minikube/releases
		(download with curl or manually)

	$ kubectl version
	$ minikube start		# downloads iso & starts local k8s cluster, starts VMs
	$ kubectl run hello-minikube --image=gcr.io/google_containers/echoserver:1.4 --port=8080
		# deployment "hello-minikube" created to our cluster
	$ kubectl expose deployment hello-minikube --type=NodePort
		# service "hello-minikube" exposed
		## creates the service
		## type: NodePort (for one Pod) or LoadBalancer
	$ kubectl get pods --all-namespaces
		# lists running pods (all-namespaces lists system pods too)
	$ curl $(minikube service hello-minikube --url)
	$ kubectl delete deployment hello-minikube
	$ minikube stop
	
	$ kubectl get namespaces
	$ kubectl get pods -n mynamespace
	$ kubectl run myapp --image=myapp:v1 --port=8080
	$ kubectl logs myapp-somecontainerid
	$ kubectl expose deployment --port=8080 myapp --type=LoadBalancer
	$ kubectl scale deployment myapp --replicas=3
	$ kubectl set image deployment/myapp myapp=myapp:v1
	
	$ minikube docker-env		# prints environment

## Example: deployment.yaml
------------
	apiVersion: apps/v1beta2
	kind: Deployment
	metadata:
		name: myapp-deployment
	spec:
		selector:
			matchLabels:
				app: myapp-deployment
		replicas: 1
		template:
			metadata:
				labels:
					app: myapp
			spec:
				containers:
				- name: myapp
				  image: myapp:9.0		# default url: dockerhub
				  ports:
				  - containerPort: 8080
------------
	Use: apply & expose the pod to the external world as a service:
	$ kubectl apply -f ./deployment.yaml
	$ kubectl expose deployment myapp-deployment --type=NodePort [--port] [--target-port]
	$ minikube service myapp-deployment --url
		# output: http://127.0.0.1:32723 = the useable deployed service
	$ kubectl get pod
		# lists the running pods, incl name
	$ kubectl describe pod [pod-name]
	$ kubectl port-forward <pod-name> [local_port:]remote_port]
		# forwards from local machine to the pod
	$ kubectl attach <pod-name> -c <container>
		# attaches to a process that is alread running inside an existing container
		# to see its output
	$ kubectl exec [-it] <pod-name> [-c container] -- command [args..]
		# execute command in a container
		# -i passes stdin to the container
		# -t stdin is a TTY
		## kubectl exec -it mypod bash
		### whoami		# you are now inside of the container, interactively on bash
		#### root		# output of the command, run inside of the container
	$ kubectl label pods <pod-name> [--overwrite] <type> mykey1=myval1 ...
	$ kubectl run <name> --image=image [--port]
		# runs an image on the cluser
	# see kubectl ref:
		http://kubernetes.io/docs/user-guide/kubectl/v1.8/
		http://kubernetes.io/docs/user-guide/kubectl/kubectl-cheatsheet/

## Architecture
	Master, manages the nodes, contains:
		API-Server
		Scheduler
		Controller Manager
	Node = Minion = kubelet & kube-proxy & pods & docker
		kubelet = the supervisor of a machine
		kube-proxy = responsible for the network configuration

## Scaling through replication configuration
	replica setting in your deployment definition YAML
		or
	Define a ReplicaSet
		or
	Bare Pods
		or
	Define a Job
		or
	DaemonSet
		or
	$ kubectl scale --replicas=4 deployment/myapp-deployment
		# check with
		$ kubectl get deployments
			or
		$ kubectl describe deployments	# lists new ReplicaSet
		# but: kubectl expose --type=NodePort works only for ONE pod!
		# solution: use
		$ kubectl expose deployment myapp-deployment --type=LoadBalancer --port=8080 --target-port=8080 --name myapp-load-balancer
			and
		$ kubectl describe services myapp-load-balancer
			# see IP address of the created load-balancer service

## Deployment
	Deployment = App & Pod & ReplicaSet
	Possible Tasks:
		Create, Update, Apply rolling updates to Pods running on a cluster
		Rollback to previous version
		Pause & Resume a deployment

	$ kubectl get deployments	#lists running deployments, incl. replicas
	$ kubectl rollout status deployment <name>
		# check status
	$ kubectl set image <deployment> <container-name>=<name>
	$ kubectl set image deployment/myapp-deployment myapp=myapp:9.0.1
		# sets/updates docker image of a deployment
	$ kubectl rollout history <deployment> [--revision={\d+}]
		# view history of a rollout, incl previous versions

## Labels & Selectors
	Label = key-value pair, you can label deployment & service & node
	Selector = select objects based on label
	
	"nodeSelector" is a property on a deployment to choose nodes
	$ kubectl label node <node-name> mykey=myvalue
	set selector in YAML:

## Example Labels & Selectors
------------
	apiVersion: apps/v1beta2
	kind: Deployment
	metadata:
		name: myapp-deployment
	spec:
		selector:
			matchLabels:
				app: myapp
		replicas: 4
		template:
			metadata:
				labels:
					app: myapp
			spec:
				containers:
				- name: myapp
				  image: myapp:9.0
				  ports:
				  - containerPort: 8080
				nodeSelector:
					mykey: myvalue			# use just nodes with this label!
------------
	$ kubectl apply -f ./deployment.yaml	# update configuration!

## Health Check
	Two types:
	Readiness Probe:
		is the Pod ready & started & loaded, the image is ready to take requests
	Liveness Proble:
		is the Pod healthy (after it has become ready)

	You can define an HTTP/TCP/CMD in your YAML to check healthiness.
------------
	apiVersion: apps/v1beta2
	kind: Deployment
	metadata:
		name: myapp-deployment
	spec:
		selector:
			matchLabels:
				app: myapp
		replicas: 4
		template:
			metadata:
				labels:
					app: myapp
			spec:
				containers:
				- name: myapp
				  image: myapp:9.0
				  ports:
				  - containerPort: 8080
				  livenessProbe:
					httpGet:
						path: /
						port: 8080
					initialDelaySeconds: 30
					periodSeconds: 30
				  readinessProbe:
					httpGet:
						path: /
						port: 8080
					initialDelaySeconds: 15
					periodSeconds: 3
------------

## Web Interface = Dashboard UI
	Use
	$ kubectl proxy
	to be able to access the dashboard from outside of the network
	http://localhost:8001/ui	#where loalhost = k8s-master
	Offers the same functions as kubectl, visually view/edit: eg. nodes (incl labels), deployments, pods, ...)
	The dashboard is mostly preinstalled, sometimes needs to be installed extra:
	$ kubectl create -f https://raw.githubusercontent.com/kubernetes/dashboard/master/src/deploy/recommended/kubernetes-dashboard.yaml

## Miscellaneous
	Third party tools:
		Kubernetes package manager
	