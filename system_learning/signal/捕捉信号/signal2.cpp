#include <iostream>
#include <signal.h>
//#include <errno.h>
#include <unistd.h>

typedef void (*sighandler_t) (int); // 函数指针

void catchsigint(int signo)
{
    printf("-----------------catch\n");
}

int main(void)
{
    sighandler_t handler;

    handler = signal(SIGINT, catchsigint);
    if (handler == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    while (1);
    
    return 0;
}
