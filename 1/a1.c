#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t pid2;
    int fd1[2],fd2[2];
    pipe(fd1);
    pipe(fd2);
    // [0] - read, [1] - write
    char s[1001];
    scanf("%s",s);
    char s1[10001];


    pid2 = fork();
    if (pid2 == 0){
        //child
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0],s1,sizeof(s1));;

        int fd = open(s1,O_CREAT | O_RDONLY,0644);

        char s2[1001];
        read(fd,s2,sizeof(s2));
        int buc = 0;

        for (int i = 0 ; i < strlen(s2) - 2 ; i ++){
            if (s2[i] == 'a' && s2[i+1] == 'b' && s2[i+2] == 'c'){
                buc ++;
            }
        }
        write(fd2[1],&buc,sizeof(int));
        close(fd1[0]);
        close(fd2[1]);
    }
    else {
        //parent
        close(fd1[0]); // read
        close(fd2[1]); // write

        write(fd1[1],s,strlen(s));
        int buc;
        read(fd2[0],&buc,sizeof(int));
        printf("%d\n",buc);

        close(fd1[1]);
        close(fd2[0]);

        wait(NULL);
    }
}
