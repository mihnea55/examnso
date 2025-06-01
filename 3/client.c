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
    char s[1001];
    int N;
    waiter = sem_open("/waiter",O_CREAT | O_RDWR,0644,0);

    scanf("%s %d",s,&N);
    int shmFd = shm_open(s, O_RDWR | O_CREAT, 0644);
    ftruncate(shmFd, sizeof(int));
    if (s[0] != '/'){
        perror("nuuu");
        return 0;
    }


    if (fork() == 0){
        char s1[1001];
        sprintf(s1,"%d",N);
        execlp("./server","server",s,s1,NULL);
        exit(1);
    }

    sem_wait(waiter);

    unsigned int* shm_ptr = mmap(NULL,sizeof(int),PROT_READ,MAP_SHARED,shmFd,0);
    printf("%d\n",shm_ptr[0]);

    wait(NULL);
    sem_close(waiter);
    sem_unlink("/waiter");
    shm_unlink(s);
}
