#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void)
{
	// 匿名映射，由于不使用文件，所以大小可以任意指定，文件描述符为-1
	// 1.在linux下实现
	int *p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);  //MAP_ANONYMOUS
	if(p == MAP_FAILED){		//注意:不是p == NULL
		perror("mmap error");
		exit(1);
	}
	// 2.在unix下实现
	int fd = open("/dev/zero", O_RDWR);
	int *p = mmap(NULL, 400, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED){		//注意:不是p == NULL
		perror("mmap error");
		exit(1);
	}

	pid_t pid = fork();				//创建子进程
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//释放映射区

	return 0;
}
