// cc -shared -m32 ./test_lib2.c ./memutils.c -o ./test_lib2.so -ldl
#include <stdio.h>
#include <signal.h>
#include <dlfcn.h>

typedef int tsigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
static tsigaction* real_sigaction1 = NULL;
static tsigaction* real_sigaction3 = NULL;


// This is our hooked one for this module.
int x_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){
    printf("Hook from library 2\n"); 
    return real_sigaction1(signum,act,oldact);
    
}

void __attribute__((constructor)) test_lib_init_2(); 

void test_lib_init_2(){
    printf("Test Lib 2 Init...\n");   
    HotPatch_patch("libc.so.6","sigaction",0,x_sigaction, (void**)&real_sigaction1);
}
