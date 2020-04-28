#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<iostream>

using namespace std;

const int n = 5;

time_t end_time;
sem_t mutex,customers,barber;
int count=0;



void* barber_func(void *arg)
{	
	while((time(NULL)<end_time || count>0)==1)
	{
		sem_wait(&customers);           
		sem_wait(&mutex);
		count--;
		cout<<"Barber cuts hair\n";
		cout<<"Customer Count: "<<count<<endl<<endl;
		sem_post(&mutex);
		sem_post(&barber);
		sleep(3);       
	}
}

void* customer_func(void *arg)
{
	while(time(NULL)<end_time)
	{
		sem_wait(&mutex);
		if(!(count>=n))
		{
			count++;
			cout<<"New Customer\n";
			cout<<"Customer Count: "<<count<<endl<<endl;
			sem_post(&mutex);
			sem_post(&customers);
			sem_wait(&barber);
		}
		else
			sem_post(&mutex);

		sleep(1);
	}
}


int main()
{
	pthread_t id1,id2;
	end_time=time(NULL)+10;

	
	sem_init(&mutex,0,1);
	sem_init(&customers,0,0);
	sem_init(&barber,0,1);

	pthread_create(&id1,NULL,barber_func,NULL);
	pthread_create(&id2,NULL,customer_func,NULL);

	pthread_join(id2,NULL);
	pthread_join(id1,NULL);

	exit(0);
}
