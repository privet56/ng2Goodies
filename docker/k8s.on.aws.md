# EKS = Kubernetes on AWS
1. EKS = k8s on AWS, is HA
2. kubectl communicates to an EKS cluster
3. k8s ServiceType: LoadBalancer exposes the service externally using the cloud providers load balancer (the other types (NodePort & ClusterIP) are automatically created)
4. seldom used ServiceType's:
    1. NLB (network load balancer, activated by an annotation)
    1. ExternalName : creates a DNS entry
5. Ingress = Entry point to your cluster with routing (host based or path based)
    1. implementation on AWS: ALB Ingress Controller
6. Security solutions: kube2iam, kiam, iam4kube, kube-aws-iam-controller
7. Logging: EFK = Fluentd & Elasticsearch & Kibana. See: https://eksworkshop.com/logging/
8. Create EKS Cluster: specify:
    1. name
    2. Role: AmazonEKSClusterPolicy & AmazonEKSServicePolicy
    3. VPC & Subnets & Security group
        1. Provide all subnets that will host k8s resources: load balancers and worker nodes
        2. subnets can be public, private or both
            1. run worker nodes on private subnets
            2. run load balancer on public subnets
        3. EKS will tag the subnets with kubernetes.io/cluster/<cluster-name> = shared
        4. subnets that will host internal load balancers need the tag kubernetes.io/role/internal-elb = 1
        5. plan ahead with subnet sizes! Pods each consume a VPC IP address
        6. /24 subnet = 254 IPs total. Substract one for each node in your cluster, and the remainder is what you have for pods (probably not enough!)
        7. the security group defines connectivity between the k8s control plan and worker nodes
            1. at minimum, k8s needs 443 inbound and 10250 outbound
            2. this security group needs permissions that align with the worker node security group

9. EKS optimized AMI: https://github.com/awslabs/amazon-eks-ami
```sh
aws eks update-kubeconfig --name my-cluster
/etc/eks/bootstrap.sh [options] <cluster-name>  # sh provided by amazon
/etc/eks/bootstrap.sh ${clusterName} ${BootstrapArguments}  # called by CloufFormatoin
```
10. CloudFormation supports bootstrap.sh - arguments (BootstrapArguments)
11. Alternative to EKS: k8s on AWS with kops:

<img src=k8s.to.aws.kops.png width="550px">

12. manual setup of HA k8s on AWS:

<img src=k8s.on.aws.ha.manual.setup.png width="550px">

13. Config: Deployment.yaml

<img src=k8s.on.aws.deploymentyaml.png width="550px">
<img src=k8s.on.aws.networkpolicyyaml.png width="550px">

## Create EKS Cluster, Doing on the AWS Web UI:
1. Create an IAM Role, select here EKS policies: AmazonEKSClusterPolicy & AmazonEKSServicePolicy
2. Create VPC & Security Group, eg. with an AWS-provided CloudFormation template
    1. see CloudFormation Template URL on 
    https://docs.aws.amazon.com/de_de/eks/latest/userguide/getting-started.html#programlisting#code-btn-container
    (copy the SecurityGroup-ID, Subnet-ID, VPC-ID created when CloudFormation Stack created)
3. Create an EKS Cluster, give it a name, select created IAM Role, VPC-ID, SecurityGroup -> [Create]
4. install kubectl (kubectl.exe) (https://docs.aws.amazon.com/eks/latest/userguide/install-kubectl.html)
    1. aws --version # python 3.x based AWS CLI should be have installed
    2. aws eks -update-kubeconfig --name {clutername}   # writes ~/.kube/config
5. install AWS IAM Authenticator (aws-iam-authenticator.exe)(https://docs.aws.amazon.com/de_de/eks/latest/userguide/getting-started.html)
6. Create Worker Nodes (EC2 instances) with CloudFormation Template (specify stack name & cluster name, SecurityGroup, AMI, keypair-name (EC2->KeyPair->Create), VPC-ID, Subnets, min/max node numbers) -> [Create Stack]
7. apply a ConfigMap:
```yml
apiVersion: v1
kind: ConfigMap
metadata:
    name: aws-auth
    namespace: kube-system
data:
    mapRoles: |
        - rolearn: arn:aws:iam::myid:role/...           # Outputs->NodeInstanceRole of the above created CloudFormation Stack, node instance role
          username: system:node:{{EC2PrivateDNSName}}
          groups:
            - system:bootstrappers
            - system:nodes
```
> $ kubectl apply -f aws-iam-authentication.yaml
7. kubectl get nodes # lists AWS cluster worker nodes
8. Create & apply Deployment.yaml (cmd: kubectl create -f Deployment.yaml):
```yml
apiVersion: apps/v1
kind: Deployment
metadata:
    name: nginx
spec:
    selector:
        matchLabels:
            run: nginx
    replicas: 2
    tmeplate:
        metadata:
            labels:
                run: nginx
        spec:
            containers:
            - name: nginx
              image: nginx:1.7.9
              ports:
              - containerPort: 80
```
8. Create & apply Service.yaml (cmd: kubectl create -f Service.yaml):
```yml
apiVersion: v1
kind: Service
metadata:
    name: myService
    labels:
        run: nginx
spec:
    ports:
    - port: 80
      protocol: TCP
    selector:
        run: nginx
    type: LoadBalancer
```
9. cmd: kubectl get services cmd: kubectl describe svc myService -> browser-accessible URL of the LB is available!

### Advanced Stuff
#### Flux
1. flux = k8s deployment (=containers deployed in k8s, looking for helm releases, has helm-operator)
2. flux is a CI/CD tool

<img src=k8s.HelmReleaseyaml.png width="550px">

3. helm works fine with EKS
4. Setup EKS with TerraForm (TerraForm =~ more-advanced CloudFormation): https://www.terraform.io/docs/providers/aws/guides/eks-getting-started.html
5. is your AWS/EKS context set up correctly? check with
```sh
kubectl config get-contexts
echo $KUBECONFIG
export KUBECONFIG=/Users/me/.kube/my-config1    # you can replace
export KUBECONFIG=$KUBECONFIG:/Users/me/.kube/my-config # you can append -> you have now >1 contexts!
kubectl config current-context
```
6. CI/CD in the cloud (SaaS): CodeShip (with CLI: ./jet)
