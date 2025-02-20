#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 8088
#define MAXLINE 1024
//driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;
	//creating socket file descriptor
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("socket creation failed. ");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr,0,sizeof(servaddr));
	//filling server information
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	int n,len;
	strcpy(buffer,"TIME");
	sendto(sockfd,buffer,strlen(buffer),MSG_CONFIRM,(const struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("Time Request Sent.\n");
	n=recvfrom(sockfd,(char*)buffer,MAXLINE,MSG_WAITALL,(struct sockaddr*)&servaddr,&len);
	buffer[n]='\0';
	printf("Time from server : %s\n",buffer);
	close(sockfd);
	return 0;
}
