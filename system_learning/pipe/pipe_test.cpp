#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
int main(){
	int fd[2]; // fd[0]读端,fd[1]写端
	int ret = pipe(fd);
	if(ret == -1){
		perror("pipe error");
		exit(1);
	}
	// 我们规定从父进程写入数据，从子进程读取数据
	// 为了保证数据的单项流动，应该关闭父进程的读端，同时关闭子进程的写端
	pid_t pid = fork();
	if(pid == -1){
		perror("fork error");
		exit(1);
	}else if(pid == 0){
		close(fd[1]);
		char buf[1024];
		ret = read(fd[0], buf, sizeof(buf));//从读端读取数据打印到屏幕上
		// read如果读取成功，返回读取的bit数，如果不成功，返回-1，如果读到文件末尾，返回0
		if(ret == EOF){
			std::cout << "读取成功" << std::endl;
		}
		write(STDOUT_FILENO, buf, ret);
		close(fd[0]);
	}else {
		close(fd[0]);
		const char * str = "hello pipe\n";
		write(fd[1],str, strlen(str));
		std::cout << "写入数据成功\n";
		wait(NULL);
		close(fd[1]);

	}
	return 0;
}
