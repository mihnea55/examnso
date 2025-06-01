#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
int ctr = 0;
sem_t *lock;
pthread_mutex_t lock1;
void    *thread_function(void *used){
    for (int i = 0 ; i < 1000000 ; i ++){
        pthread_mutex_lock(&lock1);
        ctr ++;
        pthread_mutex_unlock(&lock1);
    }
    return NULL;
}
int main(){
    pthread_t tid[3];
    sem_unlink("/1234");
    lock = sem_open("/1234",O_CREAT | O_EXCL, 0644,1);

    pthread_mutex_init(&lock1, NULL);
    for (int i = 0 ; i < 3 ; i ++){
        pthread_create(&tid[i],NULL,thread_function,NULL);
    }
    for (int i = 0 ; i < 3 ; i ++){
        pthread_join(tid[i],NULL);
    }
    printf("%d\n",ctr);
}
