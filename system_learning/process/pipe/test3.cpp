#include <iostream>
#include <unistd.h>
#include <cstring>

void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main() {
	/*
	 * 可以分析得到，不可能一写多读
	 * 下边的验证可知，不能多写一读
	 * */
	int fd[2]; // fd[0]读，fd[1]写
	int ret = pipe(fd);// 构建管道
	if(ret == -1)
		system("fork error");
	pid_t  pid; // 创建子进程
	int i;
	for(i = 0; i < 2; i++){
		if((pid = fork()) == 0)
			break;
		else if(pid == -1) 
			system("fork error");
	}
	if(i == 0){ //进程1写入数据
		sleep(1);
		close(fd[0]);
		write(fd[1], "process1", strlen("process1"));
	} else if(i == 1){// 进程2写入数据
		sleep(2);
		close(fd[0]);
		write(fd[1], "process2", strlen("process2"));
	}else { // 父进程读取数据并打印到屏幕
		close(fd[1]);
		char * buf[1024];
		int len = read(fd[0], buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);

		for(int j = 0; i < 2; j++)
			wait(NUll);
	}
	return 0;
}
