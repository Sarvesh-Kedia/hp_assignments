#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <random>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 10;

int buffer[BUFFER_SIZE];
int index=0;

sem_t full_sem,empty_sem;
pthread_mutex_t mutex;

void* producerfunc(void* arg){
	while(1){
		sleep(1);
		sem_wait(&empty_sem);
			pthread_mutex_lock(&mutex);
				int item = rand()%100;
				buffer[index++] = item;
				cout<<"Producer inserted into buffer "<<item<<endl;
				cout<<"Buffer Pos: "<<index<<endl<<endl;
			pthread_mutex_unlock(&mutex);
		sem_post(&full_sem);
	}
}

void* consumerfunc(void* arg){
	while(1){
		sleep(1);
		sem_wait(&full_sem);
			pthread_mutex_lock(&mutex);
				int item = buffer[--index];
				cout<<"Consumer removed from the buffer "<<item<<endl;
				cout<<"Buffer Pos: "<<index<<endl<<endl;
			pthread_mutex_unlock(&mutex);
		sem_post(&empty_sem);
	}
}


int main(){
	pthread_t producer,consumer;

	sem_init(&empty_sem,0,BUFFER_SIZE);
	sem_init(&full_sem,0,0);
	pthread_mutex_init(&mutex,NULL);

	cout<<"Buffer Size: "<<BUFFER_SIZE<<endl;


	pthread_create(&producer,NULL,producerfunc,NULL);
	pthread_create(&consumer,NULL,consumerfunc,NULL);
	
	pthread_exit(NULL);
}