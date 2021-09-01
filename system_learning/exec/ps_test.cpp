#include <iostream>
#include <unistd.h>
#include <fcntl.h>
int main() {
	// 将当前的进程信息打印到相应的文件中
	// 获取进程信息使用ps aux,在命令行情况下，我们需要重定向> file
	int fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd < 0){
		perror("open file failed.");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	//下边的函数一旦调用成功就会去执行另外一个程序，所以在该语句后面的任何语句都不会执行
	execlp("ps", "ps", "aux", NULL);// ps aux会打印进程信息到屏幕上，而由于dup2的重定向使得标准输出到文件中而非屏幕上
	return 0;
}
