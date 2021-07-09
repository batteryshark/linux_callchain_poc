// cc -shared -m32 ./test_lib.c ./memutils.c -o ./test_lib.so -ldl
#include <stdio.h>
#include <signal.h>
#include <dlfcn.h>

typedef int tsigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
static tsigaction* real_sigaction2 = NULL;


// This is our hooked one for this module.
int sigaction_1(int signum, const struct sigaction *act, struct sigaction *oldact){
    printf("Hook from library 1\n"); 
    return real_sigaction2(signum,act,oldact);
    
}

void __attribute__((constructor)) test_lib_init_1(); 

void test_lib_init_1(){
    printf("Test Lib 1 Init...\n");

    HotPatch_patch("libc.so.6","sigaction",0,sigaction_1, (void**)&real_sigaction2);
}
