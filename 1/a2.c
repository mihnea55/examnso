#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
typedef struct {
    char a;
    char b;
}LTR;

char sir[1001];
void *thread_function(void *used){
    LTR *ltr = (LTR *) used;
    int bucA = 0;
    int bucB = 0;
    for (int i = 0 ; i < strlen(sir) ; i ++){
        if (sir[i] == ltr->a){
            bucA++;
        }
        if (sir[i] == ltr->b){
            bucB++;
        }
    }
    for (int i = 0 ;  i < strlen(sir) ; i ++){
        if (sir[i] == ltr->a && bucA % 2 == 0){
            sir[i] -= 32;
        }
        if (sir[i] == ltr->b && bucB % 2 == 0){
            sir[i] -= 32;
        }
    }
    return NULL;
}
int main(int argc, char *argv[]){
    int N  = atoi(argv[1]);
    if (N > strlen(argv[2]) || N > 10){
        perror("offff");
        return 0;
    }
    LTR ltr[N];
    pthread_t tid[N];
    strcpy(sir,argv[2]);

    for (int i = 0 ; i < N ; i ++){
        ltr[i].a = 'a' + i;
        ltr[i].b = 'z' - i;
        pthread_create(&tid[i],NULL,thread_function,&ltr[i]);
        pthread_join(tid[i],NULL);
    }
    printf("%s\n",sir);
}
