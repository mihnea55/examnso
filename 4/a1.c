#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>
typedef struct{
    int id;
    int total;
    char *cuv;
}STR;
void *thread_function(void *used){
    STR *s = (STR *) used;

    char *cuv = strtok(s->cuv," ");
    char cuv_final[1001];
    int buc = 0;
    while (cuv != NULL){
        buc ++;
        strcpy(cuv_final,cuv);
        cuv = strtok(NULL, " ");
    }
    printf("%d\n",buc);
    if (s->total == s->id){
        printf("%s\n",cuv_final );
    }
    return NULL;
}
int main(int argc, char *argv[]){
    int fd = open(argv[1],O_CREAT | O_RDONLY,0644);
   /* if (fork() == 0){
        dup2(fd,STDIN_FILENO);
        close(fd);
        execlp("wc","wc","-l",(char*)NULL);
    }*/

    char buffer;
    int ctr = 0;
    int m = 0;
    char  lines[1024][1024];

    while (read(fd,&buffer,1)){
        if (buffer == '\n'){
            lines[ctr][m] = '\0';
            m = 0;
            ctr ++;
        }
        else {
            lines[ctr][m++] = buffer;
        }
    }
    pthread_t tid[ctr];
    STR str[ctr];
    for (int i = 0 ; i < ctr ; i ++){
        str[i].cuv = lines[i];
        str[i].id = i + 1;
        str[i].total = ctr;
    }

    for (int i = 0 ;  i < ctr ; i ++){
        pthread_create(&tid[i],NULL,thread_function,&str[i]);
         pthread_join(tid[i],NULL);
    }
   /* for (int i = 0 ; i < ctr ; i ++){
        pthread_join(tid[i],NULL);
    }*/
}
