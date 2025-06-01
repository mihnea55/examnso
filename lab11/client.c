#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME1 "l11_my_fifo"
#define FIFO_NAME2 "l12_my_fifo"
typedef struct{
    int a;
    int b;
    char c;
} OP;

int main(int argc,char *argv[]){
    int fd1 = open(FIFO_NAME1,O_WRONLY);
    int fd2 = open(FIFO_NAME2,O_RDONLY);
    for (;;){
        OP res;
        scanf("%d%d %c",&res.a, &res.b, &res.c);
        write(fd1,&res,sizeof(OP));
        if (res.c == 'x'){
            break;
        }
        int rez;
        read(fd2,&rez,sizeof(int));
        printf("\n%d\n",rez);
    }
    close(fd1);
    close(fd2);
}
