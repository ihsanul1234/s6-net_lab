#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000],client_message[2000];
	int server_struct_length=sizeof(server_addr);
	
	//clean buffers:
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//create socket:
	socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if(socket_desc<0)
	{
		printf("Error while creating socket\n");
		return -1;
	}
	printf("socket created successfully\n");
	
	//set port and ip:
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(4000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	while(1)
	{
		//get input from the user:
		printf("Enter the message : ");
		fgets(client_message, sizeof(client_message), stdin);
		client_message[strcspn(client_message,"\n")]='\0';
	
		//send the message to server:
		if(sendto(socket_desc,client_message,strlen(client_message),0,(struct sockaddr*)&server_addr,server_struct_length)<0)
		{
			printf("unable to send message\n");
			return -1;
		}
	
		//receive the server's  response:
		if(recvfrom(socket_desc,server_message,sizeof(server_message),0,(struct sockaddr*)&server_addr,&server_struct_length)<0)
		{
			printf("Error while receiving server's msg\n");
			return -1;
		}
		printf("server's response : %s\n",server_message);
	}
	
	//close the socket:
	close(socket_desc);
	
	return 0;
}
		
	
