# CI/CD with Jenkins and Kubernetes
Both Jenkins and Kubernetes can be set up & used in the cloud
The Jenkins VM should also have docker running (check with 'sudo docker version')
## Build and push Docker image
	GCP -> open shell
	git clone your app (incl. Dockerfile)
	$ docker build . -t myapp
	$ docker run -d -p80:80 --name myapp myapp	# you you can test the app
	$ docker tag myapp me/myapp
	$ docker login -u me -p mypwd
	$ docker push me/myapp
## Deploy to Kubernetes
	GCP -> open shell
	$ kubectl create deployment myapp --image me/myapp	# better you a YML file
	$ kubectl expose deployment/myapp --port=80 --name=myappsvc --type=LoadBalancer
## Configure Jenkins on the Web UI
	Update Jenkins URL in
		Manage Jenkins -> Configure System -> set Environment variables
			DOCKER_HUB_PASSWORD (+value) Add Docker Hub password
			Jenkins URL (put here the public(=external) IP address given by GCP), eg. http://35.194.167.34:8080/
	Add Webhook endpoint in
		Manage Jenkins -> Configure System -> Github -> Override Hook URL: http://35.194.167.34:8080/github-webhook/
## Configure Github
	Add URL http://<jeninkins-ip>:8080/github-webhook/ , eg. http://35.194.167.34:8080/github-webhook/
	on the Github UI, goto Settings -> Integrations & Services -> Add & Choose Jenkins (github plugin)
		set Jenkins Hook url here (http://35.194.167.34:8080/github-webhook/)
			(after commit, this hook will be called)
## Create new Job in Jenkins
	Add Github Repo
	The job will do: git-clone, compile & build docker image, push and update kubernetes
	On the Jenkins UI:
	Create new Job -> choose freestyle project, give it a name
		... configure now the project:
	General & Source Code Management Tab:
		Activate GitHub project -> set GitHub URL (incl. .git suffix), set branch (eg. */master)
			(you can use private repos too)
		Source Code Management: choose git & set github URL
		Build Triggers -> Activate GitHub hook trigger for GITScm polling
			(you can choose 'Build periodically' too, with a cronjob Schedule)
## Jenkins Build Config
	On the Jenkins UI:
	Add Build Step -> invoke Ant, Gradle, shell, ...etc.
	Shell file content:
	docker build . -t $IMAGE_NAME
	docker login -u me -p ${DOCKER_HUB_PASSWORD}
	docker push $IMAGE_NAME
	# Deploy to Kubernetes
	IMAGE_NAME="me/myapp:${BUILD_NUMBER}"					# Jenkins will generate the env var ${BUILD_NUMBER} after each successful build
	kubectl set image deployment/myapp myapp=$IMAGE_NAME
	# Check deployment history
	kubectl rollout history deployment/myapp
	