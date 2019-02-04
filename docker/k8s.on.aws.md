# EKS = Kubernetes on AWS
1. EKS = k8s on AWS
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

> $ aws eks update-kubeconfig --name my-cluster

9. EKS optimized AMI: https://github.com/awslabs/amazon-eks-ami

> $ /etc/eks/bootstrap.sh [options] <cluster-name>

