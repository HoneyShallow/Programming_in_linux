#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>



int main(int argc, const char * argv[]) {
	// 打开一个文件
	int fd = open("english.txt", O_RDWR);
	printf("fd = %d\n", fd);
	// 打开另一个文件
	 int fd1 = open("temp.txt", O_WRONLY | O_CREAT, 0664);
	printf("fd1 = %d\n", fd1);

	char buf[16];
	int len = read(fd, buf, sizeof(buf));
	while(len > 0) {
		// 将上次独处的数据写入文件
		int ret = write(fd1, buf, len);
		printf("ret = %d\n", ret);
		// read
		len = read(fd, buf, sizeof(buf));
	}
	close(fd);
	close(fd1);
	return 0;
}
