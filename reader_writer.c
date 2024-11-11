#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t readlock;
sem_t writelock;
int count=0;

void *reader(void *arg)
{
	sem_wait(&readlock);
	count++;
	if(count==1)
	{
		sem_wait(&writelock);	
	}
	sem_post(&readlock);
	
	printf("\nReader is reading. ");
	
	sem_wait(&readlock);
	count--;
	if(count==0)
	{
		sem_post(&writelock);
	}
	sem_post(&readlock);
	return NULL;
}
void *writer(void *arg)
{
	sem_wait(&writelock);
	printf("\nWriter is writing");
	sem_post(&writelock);
	return NULL;
}

int main()
{
	pthread_t readers[3];
	pthread_t writers[3];
	sem_init(&readlock,0,1);
	sem_init(&writelock,0,1);
	for(int i=0;i<3;i++)
	{
		pthread_create(&readers[i],NULL,reader,NULL);
		pthread_create(&writers[i],NULL,writer,NULL);
	}
	
	for(int i=0;i<3;i++)
	{
		pthread_join(&readers[i],NULL);
		pthread_join(&writers[i],NULL);
	}
	
	sem_destroy(&readlock);
	sem_destroy(&writelock);
	return 0;
}
