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
    mkfifo(FIFO_NAME1,0600);
    mkfifo(FIFO_NAME2,0600);

    int fd1 = open(FIFO_NAME1,O_RDONLY);
    int fd2 = open(FIFO_NAME2,O_WRONLY);

    for (;;){
        OP res;
        if (read(fd1,&res,sizeof(OP)) <= 0){
            continue;
        }
        if (res.c == 'x'){
            break;
        }
        if (res.c == '+'){
            int z = res.a + res.b;
            write(fd2,&z,sizeof(int));
        }
        if (res.c == '-'){
            int z = res.a - res.b;
            write(fd2,&z,sizeof(int));
        }

    }

}
