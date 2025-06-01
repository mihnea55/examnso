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
void *thread_function(void *used){
    char *s = (char *)used;
    for (int i = 0 ; i < strlen(s) ; i ++){
        if (s[i] >= 'a' && s[i] <= 'z'){
            if (s[i] != 'z'){
                s[i]++;
            }
            else {
                s[i] = 'a';
            }
        }
    }
    printf("%s\n",s);
    int fd;
    if (strlen(s) != 7){
        fd = open("numar_litere.txt",O_CREAT | O_WRONLY, 0644);
    }
    else {
        fd = open("7.txt",O_CREAT |  O_WRONLY, 0644);
    }
    lseek(fd,0,SEEK_END);
    write(fd,s,strlen(s));
    char c = '\n';
    write(fd,&c,1);

    return NULL;

}
int main(int argc, char *argv[]){
    char cuv[1024];
    int n  =0;
    scanf("%s",cuv);
    pthread_t tid[1024];
    while (strcmp(cuv,"stop") != 0){
        pthread_create(&tid[n],NULL,thread_function,cuv);
        n ++;
        scanf("%s",cuv);
    }
    for (int i = 0 ; i < n ; i ++){
        pthread_join(tid[i],NULL);
    }
}
