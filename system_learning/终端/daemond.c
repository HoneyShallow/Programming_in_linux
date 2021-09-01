#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void mydaemond(void)
{
    // 1.创建子进程
    pid_t pid = fork();
    if (pid > 0) { // 父进程直接退出
        exit(1);
    }else if(pid == -1){
	    perror("fork error");
	    exit(1);
    }
    // 2.创建会话
     /**/
    setsid();

    int ret = chdir("/home/linux/");
    if (ret == -1) {
        perror("chdir error");  // chdir error no such diractroy or file
        exit(1);
    }

    umask(0022);

    close(STDIN_FILENO);
    open("/dev/null", O_RDWR);
    dup2(0, STDOUT_FILENO);
    dup2(0, STDERR_FILENO);
}

int main(void)
{
    mydaemond();

    while (1) {
        
    }

    return 0;
}
