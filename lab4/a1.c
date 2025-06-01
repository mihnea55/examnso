#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, char *argv[]){
    int fd1 = open("1.txt",O_RDONLY);
    int fd2 = open("2.txt", O_WRONLY | O_CREAT | O_TRUNC,0644);

   // int lineCtr=  0;
    char buffer;
    while (read(fd1,&buffer,1)){

        if (buffer == '\n'){
            lseek(fd2,0,SEEK_SET);
        }
        else {
            write(fd2,&buffer,1);
        }
    }
    write(fd2,"asdas",5);

}
