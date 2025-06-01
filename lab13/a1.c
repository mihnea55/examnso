#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd1 = open("1.c",O_CREAT | O_RDWR, 0644);
    int fd2 = open("2.c",O_CREAT | O_RDWR, 0644);

    char x,y;
    while (read(fd1,&x,1)){
        read(fd2,&y,1);
        lseek(fd1,-1,SEEK_CUR);
        lseek(fd2,-1,SEEK_CUR);
        write(fd1,&y,1);
        write(fd2,&x,1);
    }



    return 0;
}
