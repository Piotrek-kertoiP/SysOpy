#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/resource.h>
#define threadsNumber 100000

pthread_t threadsIDArray[ threadsNumber ];

int k = 0;

void *increment(){
    k = k+1;
}

int main(){

    for(int i = 0; i < threadsNumber; i++){
       	pthread_create(&threadsIDArray[i], NULL, increment, NULL);
    }

    for (int j = 0; j < threadsNumber; j++) {
	    pthread_join( threadsIDArray[j], NULL );
    }

    printf("k = %d\n", k);

    return 0;
}
