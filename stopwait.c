#include<stdio.h>
#include<stdlib.h>
int ak,seq;
int t=5,k;
int disconnect=0;
char turn='s';
int errorframe=1,errorack=1;
void sender();
void receiver();
void main()
{
	seq=0;
	while(!disconnect)
	{
		sender();
		for(k=1;k<=10000000;k++)
		{
			receiver();
		}
	}
}
void sender()
{
	static int flag=0;
	if(turn='s')
	{
		if(errorack==0)
		{
			printf("SENDER:sent packet with seq NO:%d\n",seq);
			errorframe=rand()%4;
			printf("%s\n",(errorframe==0?"Error while sending Packet":""));
			turn='r';
		}
		else
		{
			if(flag==1)
				printf("SENDER: Received ACK for packet %d\n",ak);
			if(seq==10)
			{
				disconnect=1;
				return;
			}
			seq=seq+1;
			printf("SENDER:sent packet with seq NO:%d\n",seq);
			errorframe=rand()%4;
			printf("%s\n",(errorframe==0?"Error while sending packet":""));
			turn='r';
			flag=1;
		}
	}
	else
	{
		t--;
		printf("SENDER time reducing \n");		
		if(t==0)
		{
			turn='s';
			errorack=0;
			t=5;
		}
	}
}
void receiver()
{
	static int frexp=1;
	if(turn=='r')
	{
		if(errorframe!=0)
		{
			if(seq==frexp)
			{
				printf("RECEIVER:Received packet with seq %d\n",seq);
				ak=seq;
				frexp=frexp+1;
				turn='s';
				errorack=rand()%4;
				printf("%s\n",(errorack==0?"Error while sending ACK":""));
			}
			else
			{
				printf("RECEIVER:Duplicated packet with seq %d\n",frexp-1);
				ak=frexp-1;
				turn='s';
				errorack=rand()%4;
				printf("%s\n",(errorack==0?"Error while sending ACK":""));
			}
		}
	}
}

