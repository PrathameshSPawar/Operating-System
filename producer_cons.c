#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
sem_t mutex;
int in=0,out=0;
int buffer[5]={-1,-1,-1,-1,-1};

void *producer(void *arg)
{
	sem_wait(&empty);
	sem_wait(&mutex);
	
	buffer[in]=rand()%100;
	printf("\nProduced : %d | Buffer: ",buffer[in]);
	in=(in+1)%5;
	for(int i=0;i<5;i++)
	{
		printf("%d ",buffer[i]);
	}
	printf("\n");
	
	sem_post(&mutex);
	sem_post(&full);
	return NULL;
}

void *consumer(void *arg)
{
	int val;
	do{
		sem_wait(&full);
		sem_wait(&mutex);
		printf("\nConsumed : %d | Buffer: ",buffer[out]);
		buffer[out]=-1;
		out=(out+1)%5;
		
		for(int i=0;i<5;i++)
		{
			printf("%d ",buffer[i]);
		}
		printf("\n");
		sem_post(&mutex);
		sem_post(&empty);
		sem_getvalue(&empty, &val);
	}while(val!=5);
	return NULL;
}

int main()
{
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);
	
	pthread_t producer_thread[8];
	pthread_t consumer_thread;
	for(int i=0;i<8;i++)
	{
		pthread_create(&producer_thread[i],NULL,producer,NULL);
	}
	
	pthread_create(consumer_thread,NULL,consumer,NULL);
	
	for(int i = 0; i < 8; i++)
	{
        pthread_join(producer_thread[i], NULL);
	}
    pthread_join(consumer_thread, NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	return 0;
}
