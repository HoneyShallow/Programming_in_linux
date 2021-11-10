#include <iostream>
#include <unistd.h>
#include <cstring>

void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main() {
	int fd[2]; // fd[0]读，fd[1]写
	int ret = pipe(fd);// 构建管道
	if (ret == -1)
		sys_err("pipe error");
	pid_t  pid = fork(); // 创建子进程
	if(pid == -1){
		sys_err("fork error");
	}else if(pid > 0){
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);//
		execl("/bin/ls", "ls", "-l", NULL);
	} else{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}
