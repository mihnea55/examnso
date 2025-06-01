#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int a ,b;
    char c;
    printf(">");
    scanf("%d%d %c",&a,&b,&c);
    if (fork() == 0){
        char a_str[20];
        char b_str[20];
        char c_str[20];

        sprintf(a_str,"%d",a);
        sprintf(b_str,"%d",b);

        c_str[0] = c;
        c_str[1] = '\0';

        execlp("./server","server",a_str,b_str,c_str,NULL);
        exit(1);
    }
    else {
        int status;
        wait(&status);
        printf("%d\n",WEXITSTATUS(status));
    }
}
