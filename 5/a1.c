#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
#include <dirent.h>
char paths[1024][1024];
int ctr = 0;
void search(const char* dirPath, char x){
    DIR* dir = opendir(dirPath);
    struct stat statbuf;
    char path[1024];
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0){
            if (entry->d_name[strlen(entry->d_name)-1] == x){
                snprintf(path,sizeof(path),"%s/%s",dirPath,entry->d_name);
                stat(path,&statbuf);
                if (S_ISREG(statbuf.st_mode)){
                    strcpy(paths[ctr++],path);
                }
            }

        }
    }

}
int main(int argc, char *argv[]){
    char x = 't';
    search("mihnea",x);
    for (int i = 0 ; i < ctr ; i ++){
        if (fork() == 0){
            int fd = open(paths[i],O_CREAT | O_RDONLY, 0644);
            int n = 0;
            int sum = 0;
            char buffer[1024];
            while (read(fd,&buffer[n++],1));
            char *cuv = strtok(buffer," ");
            while (cuv != NULL){
                sum += atoi(cuv);
                cuv = strtok(NULL, " ");
            }
            exit(sum);
        }
    }
    int total = 0;
    int status;
    for (int i = 0; i < ctr; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            int child_sum = WEXITSTATUS(status);
            total += child_sum;
        }
    }
    printf("%d\n",total);
}
