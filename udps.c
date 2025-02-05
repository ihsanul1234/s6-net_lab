#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr,client_addr;
	char server_message[2000],client_message[2000];
	int client_struct_length=sizeof(client_addr);
	//clean buffers
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	//create udp socket
	socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(socket_desc<0)
	{
		print("Error while creating socket\n")
		return -1;
	}
	printf("socket created successfully\n");
	//set port and ip
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s=inet_addr("127.0.0.1")
	//bind to the set port and ip
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("couldn't bind to the port\n");
		return -1;
	}
	printf("Done with binding\n");
	printf("Listening for incoming message...\n\n");
	//Receive client's message
	if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struct_length)<0)
	
	
