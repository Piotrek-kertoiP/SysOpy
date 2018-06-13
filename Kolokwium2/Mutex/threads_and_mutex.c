#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/resource.h>
#define threadsNumber 10000

pthread_t threadsIDArray[ threadsNumber ];
pthread_mutex_t mutex;

int k = 0;

void *increment(){
    pthread_mutex_lock(&mutex);
    k = k+1;
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < threadsNumber; i++){
       	pthread_create(&threadsIDArray[i], NULL, increment, NULL);
    }

    for (int j = 0; j < threadsNumber; j++) {
	    pthread_join( threadsIDArray[j], NULL );
    }

    pthread_mutex_destroy(&mutex);

    printf("k = %d\n", k);

    return 0;
}