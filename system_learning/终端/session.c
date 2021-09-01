#include <iostream>
#include <unistd.h>

int main(void)
{
    /*
     * 该程序的进程组id与bash的进程组id不同，但会话id相同
     * 经过修改，其子进程的进程组id和会话id均不同于该进程
     * */
    pid_t pid;

    if ((pid = fork())<0) {
        perror("fork");
        exit(1);

    } else if (pid == 0) {

        printf("child process PID is %d\n", getpid());
        printf("Group ID of child is %d\n", getpgid(0));
        printf("Session ID of child is %d\n", getsid(0));

        sleep(10);
        setsid();       //子进程非组长进程，故其成为新会话首进程，且成为组长进程。该进程组id即为会话进程

        printf("Changed:\n");

        printf("child process PID is %d\n", getpid());
        printf("Group ID of child is %d\n", getpgid(0));
        printf("Session ID of child is %d\n", getsid(0));

        sleep(20);

        exit(0);
    }

    return 0;
}
