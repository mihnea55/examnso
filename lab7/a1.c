#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>


typedef struct{
    int id;
} TH_STRUCT;
void *test(void *param){
    int id = *(int *)param;
    printf("%d\n",id);
    sleep(10000);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t tid[100000];
    int id[100000];
    for (int i = 0 ; i < 100000 ; i ++){
        id[i] = i + 1;
    }
    for (int i = 0 ; ; i ++){
        pthread_create(&tid[i],NULL,test,&id[i]);
        pthread_join(tid[i],NULL);
    }
}
