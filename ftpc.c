/*ftp server*/
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	FILE *fp;
	int csd,newsd,ser,n,s,cli,cport;
	char name[100],fname[100],rcvmsg[100],rcvg[100];
	struct sockaddr_in servaddr;
	printf("Enter the port\n");
	scanf("%d",&cport);
	csd=socket(AF_INET,SOCK_STREAM,0);
	if(csd<0)
	{
		printf("error ...\n");
		exit(0);
	}
	else
		printf("socket is created \n");
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(cport);
	if(connect(csd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
		printf("error in connection\n");
	else
		printf("connected!\n");
	printf("enter the existing file name\t");
	scanf("%s",name);
	printf("enter the new file name\n");
	scanf("%s",fname);
	fp=fopen(fname,"w");
	send(csd,name,sizeof(name),0);
	while(1)
	{
		s=recv(csd,rcvg,100,0);
		rcvg[s]='\0';
		if(strcmp(rcvg,"error")==0)
			printf("file is not available\n");
		if(strcmp(rcvg,"completed")==0)
		{
			printf("file is transferred ...\n");
			fclose(fp);
			close(csd);
			break;
		}
		else
		fputs(rcvg,stdout);
		fprintf(fp,"%s",rcvg);
		return 0;
	}
}
