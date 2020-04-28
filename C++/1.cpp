#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t wrt;
pthread_mutex_t mutex;
int data = 0;
int readers = 0;

void* writer(void *threadid)
{   
    sem_wait(&wrt);
    data += 5;
    printf("writing: new updated data = %d\n",data);
    sem_post(&wrt);

}

void* reader(void *threadid)
{   
        // increment numreader
        pthread_mutex_lock(&mutex);
        
                readers++;

        pthread_mutex_unlock(&mutex);


        sem_wait(&wrt);

                printf("reading: data = %d\n", data);

        sem_post(&wrt);


        pthread_mutex_lock(&mutex);

                readers--;

        pthread_mutex_unlock(&mutex);
}



int main(){   

    pthread_t read_thread[10],write_thread[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    for(int i = 0; i < 5; i++) {
        pthread_create(&read_thread[i], NULL, reader, (void *)i);
    }
    for(int i = 0; i < 3; i++) {
        pthread_create(&write_thread[i], NULL, writer, (void *)i);
    }

    
    
    for(int i = 0; i < 3; i++) {
        pthread_join(read_thread[i], NULL);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(write_thread[i], NULL);

    }

    for(int i = 3; i < 5; i++) {
        pthread_join(read_thread[i], NULL);
    }
    

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
