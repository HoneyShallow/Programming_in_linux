#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#define MSG_TRY "try again\n"

int main() {
	char buf[10];
	int fd, n;
	// /dev/tty---> 当前打开的终端设备
	fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	// 设置为非阻塞
	if(fd < 0) {
		perror("open /dev/tty");
		exit(1);
	}
	tryagain:
	n = read(fd, buf, 10);
	if(n <  0) {
		// 如果write 为阻塞，但是没有数据可读，此时全局变量errno 被设置为EAGAIN
		if(errno == EAGAIN) {
			sleep(3);
			write(STDIN_FILENO, MSG_TRY, strlen(MSG_TRY));
			goto tryagain;
		}
		perror("read /dev/tty");
		exit(1);
	}
	write(STDOUT_FILENO, buf, n);
	close(fd);
}
