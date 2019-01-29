# Securing Kubernetes

1. on the host: use a minimal distro
	1. see: https://itnext.io/securing-the-base-infrastructure-of-a-kubernetes-cluster-64e79646b7bf
	2. example:  CoreOS Container Linux, Ubuntu Core, and the Atomic Host 
2. secure host OS
	https://github.com/aquasecurity/kube-bench
3. Secure Docker as per best-practices:
	https://dev.to/petermbenjamin/docker-security-best-practices-45ih
4. secure the k8s admin console
	1. see: https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/
5. *cloud security settings
	1. see: https://www.altoros.com/blog/improving-security-for-kubernetes-deployments-at-scale/
	2. use multi-factor authentication for all access
	3. choose the correct authentication method for k8s
		1. see: https://medium.com/@etienne_24233/comparing-kubernetes-authentication-methods-6f538d834ca7
	4. on Azure, use CNI
		1. see https://www.danielstechblog.io/kubernetes-network-policies-on-azure-kubernetes-service-with-azure-npm/
		2. see https://docs.microsoft.com/en-us/azure/virtual-network/kubernetes-network-policies
	5. Use SSL for all servers
	6. Use Zero Trust Network
		1. see http://www.virtualstarmedia.com/downloads/Forrester_zero_trust_DNA.pdf
6. build a Pod security policy
	1. Build a pod security policy by preventing pods from running as root, as well as from accessing host ports and certain volume types
	2. see: https://itnext.io/the-abc-of-kubernetes-access-control-e7d280af5c88
7. Configure your Kubernetes pods to run read-only file systems
8. Restrict privilege escalation in Kubernetes with role-based access control
9. Cloud Native Computing Foundation (CNCF); 9 Kubernetes Security Best Practices:
	1. see https://www.cncf.io/blog/2019/01/14/9-kubernetes-security-best-practices-everyone-must-follow/
	2. see https://medium.com/containerum/top-security-tips-for-your-kubernetes-cluster-9b23a4e95111
	3. see https://techbeacon.com/hackers-guide-kubernetes-security
10. Apply SecDevOps best practices:
	1. see https://medium.com/devopslinks/what-is-devsecops-the-6-steps-to-secure-your-software-delivery-447906a6bd9f
	2. see https://medium.com/@arseny.chernov/securing-devops-review-of-approaches-a801742630ca

TODO!
