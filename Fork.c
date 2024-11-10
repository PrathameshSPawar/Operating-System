#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void bubble(int arr[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
	
void insertion(int arr[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		int min=i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
			{
				min=j;
			}
		}
		int temp=arr[min];
		arr[min]=arr[i];
		arr[i]=temp;
	}	
}
	
void display(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
	
int main()
{
	int n;
	printf("\nEnter the Total count of Number");
	scanf("%d",&n);
	
	int arr[n];
	printf("\nEnter the elements one by : ");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	
	printf("\n");
	pid_t pid=fork();
	
	if(pid<0)
	{
		perror("\nFork Filed to creat");
		exit(1);
	}else if(pid>0)
	{
		printf("\nParent Process (PID : %d) sorting using Bubble sorting: ",getpid());
		bubble(arr,n);
		printf("\nSorted using bubble sort : ");
		display(arr,n);
		// Wait for child to prevent it from becoming a zombie
		wait(NULL);
	}else{
		printf("\nChild Process (PID : %d) sorting using insertion sorting: ",getpid());
		insertion(arr,n);
		printf("\nSorted using Insertion sort : ");
		display(arr,n);
		// Simulate an orphan state by making parent terminate before child completes
		sleep(5);
		printf("\nChild Process(PID : %d) exiting.\n",getpid());
	}
	return 0;
}
