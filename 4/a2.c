#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

int countelements(){
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    DIR* dir = opendir(cwd);
    struct dirent *entry;
    int count =0;
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0){
            count ++;
        }
    }
    return count;

}
int main(int argc, char *argv[]){
    int f1[2];
    int f2[2];
    pipe(f1);
    pipe(f2);
    if (fork() == 0){
        // 2


        if (fork() == 0){
            // 3

            if (fork() == 0){
                //5
                close(f1[1]);
                int count;
                read(f1[0],&count,sizeof(int));
                sleep(count);
                printf("%d\n",count);
                close(f1[0]);

            }
            else {
                // 3
                char fname[1001];
                close(f2[1]);
                read(f2[0],fname,sizeof(fname));
                close(f2[0]);
                execlp("ls","ls",fname+1,NULL);
                wait(NULL);
            }
        }
        else {
            // 2
            if (fork() == 0){
                char fname[1001];
                scanf("%s",fname+1);
                close(f2[0]);
                fname[0] = strlen(fname+1);
                write(f2[1],fname,sizeof(fname));
                close(f2[1]);
            }
            int count = countelements();
            close(f1[0]);
            write(f1[1],&count,sizeof(int));
            close(f1[1]);
        }

        wait(NULL);
        wait(NULL);
    }
    else {
        // 1

        wait(NULL);
    }

}
