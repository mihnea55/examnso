#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
   // pid_t pid2, pid3, pid4, pid5;
    printf("%d->%d\n",getpid(),getppid());
    //sleep(10);
    if (fork() == 0){
        //child
        if (fork() == 0){
            printf("pid4 -> %d -> %d\n",getpid(),getppid());
        }
        else {
            printf("pid2 -> %d -> %d\n",getpid(),getppid());
            wait(NULL);
        }
    }
    else {
        //parent
        if (fork() == 0){
            if (fork() == 0){
                printf("pid5 -> %d -> %d\n",getpid(),getppid());
            }
            else {
                printf("pid3 -> %d -> %d\n",getpid(),getppid());
                wait(NULL);
            }
        }
        else {
            printf("pid1 -> %d -> %d\n",getpid(),getppid());
            wait(NULL);
            wait(NULL);
        }
    }
}
