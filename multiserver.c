#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#define PORT 8080
int main(int arge,char const*argv[])
{
	int server_fd,new_socket,valread;
	struct sockaddr_in address;
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[1024]={0};
	char* hello;
	pid_t childpid;
	//creating socket file descriptor
	if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		perror("socket failed.");
		exit(EXIT_FAILURE);
	}
	//forcefully attaching socket to the port 8080
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
