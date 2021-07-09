// cc -m32 ./test.c -o ./test
#include <stdio.h>
#include <signal.h>

#include <dlfcn.h>

int main(int argc){
    printf("THIS IS A TEST!\n");
    
    struct sigaction act;
    struct sigaction oldact;
    sigaction(0,&act,&oldact);
    
    printf("sigaction Returned!\n");
    
    
    
    return 0;
}