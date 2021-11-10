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
    exit(-1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
		// 必须指定命名管道
        printf("Enter like this: ./a.out fifoname\n");
        return -1;
    }
    int fd = open(argv[1], O_WRONLY);
    if (fd < 0) 
        sys_err("open");

    int i = 0;
    while (1) {
		char buf[4096];
        sprintf(buf, "hello itcast %d\n", i++);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}
