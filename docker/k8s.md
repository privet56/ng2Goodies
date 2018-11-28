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
	Service = endpoint that exports a port to the outside world

## kubectl & minikube
	runs k8s locally, but does not support load balancers, persistent volumes, ingress
	requires virtualization & hypervisor (kvm, Virtualbox(on linux) or VMWare(macOS or linux))
	install kubectl & minikube
	$ kubectl
	$ kubectl.exe on windows
	download url: see in the docs ( https://kubernetes.io/docs/tasks/tools/install-kubectl/ & https://github.com/kubernetes/minikube/releases )
		(download with curl or manually)

	$ kubectl version
	$ minikube start		# downloads iso & starts local k8s cluster, starts VMs
	$ kubectl run hello-minikube --image=gcr.io/google_containers/echoserver:1.4 --port=8080
		# deployment "hello-minikube" created to our cluster
	$ kubectl expose deployment hello-minikube --type=NodePort
		# service "hello-minikube" exposed
		## creates the service
	$ kubectl get pod
		# lists running pods
	$ curl $(minikube service hello-minikube --url)
	$ kubectl delete deployment hello-minikube
	$ minikube stop

## deployment.yaml
------------
	apiVersion: apps/v1beta2
	kind: Deployment
	metadata:
		name: tomcat-deployment
	spec:
		selector:
			matchLabels:
				app: tomcat-deployment
		replicas: 1
		template:
			metadata:
				labels:
					app: tomcat
			spec:
				containers:
				- name: tomcat
				  image: tomcat:9.0		# default url: dockerhub
				  ports:
				  - containerPort: 8080
------------
	Use: apply & expose the pod to the external world as a service:
	$ kubectl apply -f ./deployment.yaml
	$ kubectl expose deployment tomcat-deployment --type=NodePort [--port] [--target-port]
	$ minikube service tomcat-deployment --url
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
	$ kubectl label pods <pod-name> [--overwrite] <type> key1=val1 ...
	$ kubectl run <name> --image=image [--port]
		# runs an image on the cluser
	# see kubectl ref:
	## http://kubernetes.io/docs/user-guide/kubectl/v1.8/
	## http://kubernetes.io/docs/user-guide/kubectl/kubectl-cheatsheet/

## Architecture
	> Master, manages the nodes
	> Node = Minion = kubelet & kube-proxy & pods & docker
