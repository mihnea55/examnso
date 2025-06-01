#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int pipeid[2];

    pipe(pipeid);
    if (fork() == 0){
        // child
        char x;
        close(pipeid[1]); // scriere
        while (read(pipeid[0], &x, 1)){
            if (strchr("02468",x)){
                printf("%c\n",x);
            }
        }
        close(pipeid[0]); // citire

    }
    else {
        // parent
        int fd = open("1.txt",O_RDONLY);
        char x;
        close(pipeid[0]); // citire
        while (read(fd,&x,1)){
            if (x >='0' && x <= '9'){
                write(pipeid[1],&x,1);
            }
        }

        close(pipeid[1]);
    }

    return 0;
}
