#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int validate(const char *fname){
    int fd = open(fname,O_RDONLY,0644);

    char buffer;
    int counter = 0;
    while (read(fd,&buffer,1)){
        counter ++;
        if (buffer == '\n'){
            if (counter != 7){
                return 0;
            }
            counter = 0;
        }
        else {
            if (buffer < '0' || buffer > '9'){
                return 0;
            }
        }
    }
    return 1;
}

void getLine(const char *fname,int number){
     int fd = open(fname,O_RDONLY,0644);

    char buffer[7];
    int lineCtr = 1;
    while (read(fd,buffer,7)){
        if (lineCtr == number){
            printf("%s",buffer);
        }
        lineCtr ++;
    }
}
int maxNumber(const char *fname){
     int fd = open(fname,O_RDONLY,0644);

    char buffer[7];
    int maxim = 0;
    while (read(fd,buffer,7)){
        if (atoi(buffer) > maxim){
            maxim = atoi(buffer);
        }
    }
    return maxim;
}
void transpose(const char *src, const char *dst){
    int fd1 = open(src,O_RDONLY,0644);
    int fd2 = open(dst,O_WRONLY,0644);

    char buffer;
    for (int i = 0 ; i < 6 ; i ++){
        lseek(fd1,i,SEEK_SET);
        while (read(fd1,&buffer,1)){
            lseek(fd1,6,SEEK_CUR);
            write(fd2,&buffer,1);
        }
        char c = '\n';
        write(fd2,&c,1);
    }
}
int main(int argc, char *argv[]){
    printf("%d\n",validate("1.txt"));
    getLine("1.txt",atoi(argv[1]));
    printf("%d\n",maxNumber("1.txt"));
    transpose("1.txt","2.txt");
}
