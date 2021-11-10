#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

struct STU {
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
// 参数argc是保存的输入参数的个数，argv保存输入的参数
{
	// 读写进程虽然各自都创建了映射区，但实际上两个映射区是连接的
	// 相当于管道，虽然实现了进程间通信
    struct STU student = {10, "xiaoming", 'm'};
    if (argc < 2) {
		// 相当于参数2是文件名
        printf("./a.out file_shared\n");
        exit(-1);
    }
	// 1.建立映射区
    int fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    ftruncate(fd, sizeof(student)); // 为映射区分配足够的内存空间
	// 截断函数需要打开文件有写权限才能扩展空间
	// 打开文件隐含着一次读操作
    char * mm = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap");
    close(fd);
	// 2.写入数据
    while (1) {
		// 将student中的数据拷贝到mm处
        memcpy(mm, &student, sizeof(student));
        student.id++;// 修改student信息等待下次循环拷贝
        sleep(1);
    }
	// 由于映射空间有限，下次修改的内容会覆盖上次的内容
	// 3.解除映射
    munmap(mm, sizeof(student));
    return 0;
}
