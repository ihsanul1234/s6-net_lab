/*selective repeat*/
#include<stdio.h>
#include<stdlib.h>
int input(int a[],int frame_size)
{
	printf("\n\n Input \n\n");
	for(int i=1;i<=frame_size;i++)
	{
		printf("Enter value for frame[%d] : ",i);
		scanf("%d",&a[i]);
		printf("\n");
	}
	printf("\n\n");
	return 1;
}
int display(int a[],int frame_size)
{
	printf("\n\n Display \n\n");
	for(int i=1;i<=frame_size;i++)
	{
		printf("Frame[%d] : %d ",i,a[i]);
		printf("\n");
	}
	printf("\n\n");
	return 1;
}
int selective_repeat(int frames[],int window_size,int frame_size)
{
	int nt=0;
	int k=0;
	int left[10000]={-1};
	int i;
	for(i=1;i<=frame_size;i++)
	{
		int flag=rand()%2;
		if(flag)
		{
			printf("Frame[%d] with value %d Acknowledge !!!\n\n",i,frames[i]);
			nt++;
		}
		else
		{
			printf("frame[%d]with value %d not Acknowledged !!!\n\n",i,frames[i]);
			left[k++]=i;
			nt++;
		}
		if(i % window_size == 0)
		{
			for(int x=0;x<k;x++)
			{
				int lost_frame=left[x];
				printf("Frame[%d] with value %d retransmitted\n\n",lost_frame,frames[lost_frame]);
				nt++;
				printf("frame[%d] with value %d Acknowledged on Second Arrempt \n\n",lost_frame,frames[lost_frame]);
			}
			k=0;
		}
	}
	for(i=0;i<k;i++)
	{
		printf("frame[%d] with value %d Retransmitted\n\n",i,left[i]);
		nt++;
		printf("frame[%d] with value %d Acknowledged on second Attempt\n\n",i,left[i]);
	}
	printf("Total Transmissions : %d \n\n",nt);
	return 0;
}
int main()
{
	int frame[50];
	int window_size;
	int frame_size;
	printf("\n\n Selective Repeat \n\n");
	printf("Enter window size : ");
	scanf("%d",&window_size);
	printf("Enter Number of frames to be transmitted : ");
	scanf("%d",&frame_size);
	input(frame,frame_size);
	display(frame,frame_size);
	selective_repeat(frame,window_size,frame_size);
	return 0;
}
	
