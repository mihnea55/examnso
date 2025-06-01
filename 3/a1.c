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
char X;
int counter;
int nrFiles;
char paths[1024][1024];
sem_t lock;
sem_t slots;


void *thread_function(void *used){
    char *s = (char*)used;
    int fd = open(s,O_RDONLY,0644);
    char buffer;
    while (read(fd,&buffer,1)){
        if (buffer == X){
            sem_wait(&lock);
            counter ++;
            sem_post(&lock);
        }
    }
    sem_post(&slots);
    return NULL;
}
void search(const char* dirPath){
    DIR *dir = opendir(dirPath);
    struct stat statbuf;
    char path[1024];
    struct dirent *entry = NULL;
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0){
            snprintf(path,sizeof(path),"%s/%s",dirPath,entry->d_name);
            stat(path,&statbuf);
            if (S_ISREG(statbuf.st_mode)){
                strcpy(paths[nrFiles++],path);
            }
            if (S_ISDIR(statbuf.st_mode)){
                search(path);
            }
        }
    }
}

int main(int argc, char *argv[]){
    if (strlen(argv[2]) > 1 || argv[2][0] < 'A' || argv[2][0] > 'Z'){
        perror("hahah");
        return 0;
    }
    sem_init(&lock,0,1);
    sem_init(&slots,0,5);
    X = argv[2][0];
    search(argv[1]);
    pthread_t tid[nrFiles];
    for (int i = 0 ; i < nrFiles ;i  ++){
        sem_wait(&slots);
        pthread_create(&tid[i],NULL,thread_function,paths[i]);
    }
    for (int i = 0 ; i < nrFiles ; i ++){
        pthread_join(tid[i],NULL);
    }

    printf("%d\n",counter);


}
