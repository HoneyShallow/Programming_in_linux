#include <iostream>
#include <unistd.h>
#include <cstring>

void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main() {
	int fd[2]; // fd[0]读，fd[1]写
	pipe(fd);// 构建管道
	pid_t  pid; // 创建子进程
	int i;
	for(i = 0; i < 2; i++){
		if((pid = fork()) == 0)
			break;
	}
	if(i == 0){ //进程1用于写入数据到写端
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);//
		execl("/bin/ls", "ls", "-l", NULL);
	} else if(i == 1){// 进程2用于读取数据到读端
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
	}else {
		close(fd[0]);
		close(fd[1]);
		for(int j = 0; i < 2; j++)
			wait(NUll);
	}
	return 0;
}
