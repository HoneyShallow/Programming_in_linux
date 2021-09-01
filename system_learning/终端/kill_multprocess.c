#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n;

    if (argc < 2) { // argc表示参数个数,argv保存各参数的字符串
        printf("./a.out numchild\n");
        exit(-1);
    }

    n = atoi(argv[1]); // 将输入的字符串转化为整型值
    for (i = 0; i < n; i++) {
        if ((pid = fork()) < 0)
            sys_err("fork");
        else if (pid == 0) 
            break;
    }

    if (pid == 0) {        /* in child */
        while (1) {// 打印当前进程的进程id和进程组id
            printf("I'm child pid = %d, groupid = %d\n", getpid(), getpgrp());
            sleep(1);
        }
    }

    if (pid > 0) {      /* in parent */
        
        pid_t cpid;// 回收所有子进程
        while ((cpid = wait(NULL)) > 0)
            printf("child %d is over\n", cpid);
    }

    return 0;
}
