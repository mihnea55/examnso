#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){

    int f1[2], f2[2];

    pipe(f1);
    pipe(f2);


    if (fork() == 0){
        // child 2
        close(f1[0]); // read
        char s[1001];
        scanf("%s",s);
        write(f1[1],s,strlen(s));
        close(f2[1]);

    }
    else {
        //parent
        if (fork() == 0){
            // child 3
            close(f1[1]); // write
            char s[1001];
            int x = read(f1[0],s + 1,1000);
            s[0] = x + 4;
            s[x+1] = '\0';
            strcat(s,".txt");
            s[x+5] = '\0';

            int fd = open(s+1,O_CREAT | O_TRUNC | O_RDWR, 0644);
            for (int i = 0 ; i < getpid() ; i ++){
                char x[2];
                x[0] = 'a';
                x[1] = '\n';
                write(fd,x,2);
            }
            close(f2[0]);

            write(f2[1],s,strlen(s));

            close(f2[1]);
            close(f1[0]);
        }
        else {
            // parent
            if (fork() == 0){
                // child 4
                close(f2[1]);
                char s[1001];
                int buc = 0;

                read(f2[0],s,1001);
                s[(int)s[0] + 1] = 0;
                printf("%s\n",s);
                int fd = open(s+1,O_RDONLY,0644);
                char buffer;
                while (read(fd,&buffer,1)){
                    if (buffer == '\n'){
                        buc ++;
                    }
                }
                printf("%d\n",buc);
                execlp("wc", "wc", "-l", s + 1, (char *)NULL);
                close(f2[0]);

            }
            else {
                // parent
                wait(NULL);
            }
            wait(NULL);
        }
        wait(NULL);
    }
}
