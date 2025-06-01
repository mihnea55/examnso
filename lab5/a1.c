#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
void listRec(const char *path){
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name,".") != 0 &&
        strcmp(entry->d_name,"..") != 0){
            snprintf(fullPath,512,"%s/%s",path,entry->d_name);
            if (lstat(fullPath,&statbuf) == 0){
                printf("%s->%d\n",fullPath,entry->d_size);
                if (S_ISDIR(statbuf.st_mode)){
                    listRec(fullPath);
                }
            }
        }
    }
}
int main(){
    listRec("mihnea1");
}
