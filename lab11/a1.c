#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
sem_t hartie;
sem_t tutun;
sem_t bricheta;
sem_t primit1;
sem_t primit2;
sem_t primit3;
int x = 1;
void *thread_dealer(void *unused)
{
    for (;;){
        sleep(rand() % 3 + 1);
        x = rand() % 3 + 1;
        printf("%d\n",x);
        if (x == 1){
            sem_post(&bricheta);
            sem_post(&tutun);
            sem_post(&primit1);
        }
        if (x == 2){
            sem_post(&tutun);
            sem_post(&hartie);
            sem_post(&primit2);
        }
        if (x == 3){
            sem_post(&hartie);
            sem_post(&bricheta);
            sem_post(&primit3);
        }

    }
    return NULL;
}
void *thread_client(void *unused)
{
    int *id = (int *) unused;
    for (;;){
        if (*id == 1){
            sem_wait(&primit1);
        }
        if (*id == 2){
            sem_wait(&primit2);
        }
        if (*id == 3){
            sem_wait(&primit3);
        }
        if (*id == 1 && x == 1){
            sem_wait(&bricheta);
            sem_wait(&tutun);
        }
        if (*id == 2 && x == 2){
            sem_wait(&tutun);
            sem_wait(&hartie);

        }
        if (*id == 3 && x == 3){
            sem_wait(&hartie);
            sem_wait(&bricheta);
        }
        printf("%d A tras forta\n",*id);
    }
    return NULL;
}
int main(int argc, char *argv[]){
    sem_init(&hartie,0,0);
    sem_init(&bricheta,0,0);
    sem_init(&tutun,0,0);
    sem_init(&primit1,0,0);
    sem_init(&primit2,0,0);
    sem_init(&primit3,0,0);
    int id[3] = {1, 2, 3};
    pthread_t tid[3];
    pthread_t dealer;

    for (int i = 0 ; i < 3 ; i ++){
        pthread_create(&tid[i],NULL,thread_client,&id[i]);
    }
    pthread_create(&dealer,NULL,thread_dealer,NULL);
    for (int i = 0 ; i < 3 ; i ++){
        pthread_join(tid[i],NULL);
    }
}
