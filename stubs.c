// cc -shared -m32 ./stubs.c -o ./libc_stubs.so -ldl
#include <signal.h>
#include <dlfcn.h>

typedef int tsigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
tsigaction* real_sigaction = 0;

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){ 
    return real_sigaction(signum,act,oldact);
}


void __attribute__((constructor)) stub_init(); 

void stub_init(){
    printf("stubs init\n");
    void* lc = dlopen("libc.so.6",RTLD_NOW);
    real_sigaction = dlsym(lc,"sigaction");
}