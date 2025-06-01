#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argv[3][0] == '+'){
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);
        exit(x + y);
    }
    else {
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);
        exit(x-y);
    }
}
