#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void bubble(int arr[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
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

int main(int argc,char *argv[])
{
	int n;
	printf("\nEnter the Total Numbers: ");
	scanf("%d", &n);
	
	int arr[n];
	printf("\nEnter the Number of array one by one: ");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	printf("\n");

	
	bubble(arr,n);
	printf("\nParent Process (PID:%d) sorted array : ",getpid());
	for(int i=0;i<n;i++)
	{
		printf("%d",arr[i]);
	}
	
	printf("\n");
	pid_t pid=fork();
	if(pid<0)
	{
		perror("\nFailed to creat fork");
		exit(1);
	}else if(pid==0)
	{
		printf("\nchild process(PID :%d) created by parent process(PID%d): ",getpid(),getppid());
		char *args[n+2];
		args[0]="./child_Process";
		for(int i=0;i<n;i++)
		{
			char *num=malloc(10);
			sprintf(num,"%d",arr[i]);
			args[i+1]=num;
		}
		args[n+1]=NULL;
		if (execve(args[0], args, NULL) == -1) 
		{
            perror("execve failed");
            exit(1);
        }
	}else{
		wait(NULL);
		printf("\nParents Process(PID :%d) Finished waiting for child: ",getpid());
	}
	return 0;
}
