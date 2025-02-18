#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#define MAXLINE 1024
#define PORT 8088
//Driver code
int main()
{
	int sockfd,cp,t;
	char buffer[MAXLINE];
	time_t ct;
	struct sockaddr_in servaddr,cliaddr;
	//creating socket file descriptor
	if(sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("socket creation failed!");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));
	//filling server information
	servaddr.sin_family=AF_INET; //IPV4
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(PORT);
	//Bind the socket with the server address
	if(bind(sockfd,(const struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	int len,n;
	len=sizeof(cliaddr);//len is value/result
	while(1)
	{
		n=recvfrom(sockfd,(char*)buffer,MAXLINE

