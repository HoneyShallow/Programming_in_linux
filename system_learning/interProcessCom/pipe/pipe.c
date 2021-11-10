#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    pid_t pid;
    int fd[2];
    
   if (pipe(fd) == -1) //管道为构建成功
       sys_err("pipe");

   pid = fork(); // 创建一个子进程
   if (pid < 0) {// 创建子进程失败
       sys_err("fork err");
   } else if (pid == 0) {
	   // 如果是子进程关闭写端
        close(fd[1]);
		char buf[1024];
        int len = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);// 同样的，读取完数据后操作完成后就可以关闭
   } else {
       close(fd[0]);
	   const char *p = "test for pipe\n";
       write(fd[1], p, strlen(p));
       wait(NULL); 
	   // 由于此处使用了wait函数回收子进程，父进程阻塞直至子进程结束
       close(fd[1]);//写完数据之后工作完成就可以关闭文件了
   }
    return 0;
}
