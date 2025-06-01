#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
    unsigned int x = atoi(argv[1]);
    unsigned char *bytePtr = (unsigned char*)&x;
    for (int i = 0 ; i < 2 ; i ++){
        unsigned char aux = bytePtr[i];
        bytePtr[i] = bytePtr[3-i];
        bytePtr[3-i] = aux;
    }
    for (int i = 0 ; i < 4 ; i ++){
        printf("%d\n",bytePtr[i]);
    }
   // x = (unsigned int)&bytePtr;
    printf("%u\n",x);
}
