#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>

sem_t *waiter;
int main(int argc, char *argv[]){

    waiter = sem_open("/waiter",0);
    int shmFd = shm_open(argv[1],O_CREAT | O_RDWR,0644);
    ftruncate(shmFd, sizeof(int));
    unsigned int* shm_ptr = mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED,shmFd,0);

    int counter = 0;
    for (int i = 1 ; i <= atoi(argv[2]) ; i ++){
        if (atoi(argv[2]) % i == 0){
            counter ++;
        }
    }
    shm_ptr[0] = counter;
    sem_post(waiter);
    exit(0);

}
