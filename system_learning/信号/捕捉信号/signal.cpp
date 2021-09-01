#include <iostream>
#include <unistd.h>
//#include <errno.h>
#include <signal.h>

void do_sig(int a)
{
    printf("Hi, SIGINT, how do you do !\n");
}

int main(void)
{
	// 当产生SIGINT信号时，执行自定义函数
    if (signal(SIGINT, do_sig) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    // 每当产生SIGINT信号时执行自定义函数
    while (1) {
        printf("---------------------\n");
        sleep(1);
    }

    return 0;
}
