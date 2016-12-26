//#include "function.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Invalid number of arguments for parent\n");
        return 1;
    }
    int num = atoi(argv[1]);
    int i;
    pid_t pid, wpid;
    int status = 0;

    //Set up shared memory
    //allocate_map();

    //Create childs
    for(i = 1; i < num+1; ++i){
        pid = fork();
        //If child
        if(pid == 0){
            char child[10];
            sprintf(child,"%d",i);
            //execlp("/home/os/linuxsharechild", "child", child, NULL);
        }
        //If failed
        else if(pid < 0){
            printf("Pid failed\n");
            return 1;
        }
        //If parent do nothing
        else{
        }
    }

    //Wait for children
    printf("Parent waiting for all children to complete.\n");
    while((wpid=wait(&status))>0);
    printf("All children completed\n");
    printf("Name: Daniel Liu\tID: %d\n", 23018050);
    return 0;
}