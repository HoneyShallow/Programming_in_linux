#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("./a.out fifoname\n");
        return -1;
    }
	// 利用管道相当于使用文件，一写一读
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) 
        sys_err("open");
    while (1) {
		char buf[4096];
        int len = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        sleep(3); //多個读端时应增加睡眠秒数,放大效果.
    }
    close(fd);

    return 0;
}
