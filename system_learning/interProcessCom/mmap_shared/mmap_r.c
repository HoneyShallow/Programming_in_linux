#include <stdio.h>
#include <sys/stat.h>
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
    exit(-1);
}
/*
读进程
*/
int main(int argc, char *argv[])
{
    struct STU student;
    if (argc < 2) { // 共享文件存储数据
        printf("./a.out file_shared\n");
        exit(-1);
    }
	// 读写进程借助磁盘空间的同一段创建映射区
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        sys_err("open error");
    struct STU *mm = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
	// void* 可以隐式转换为任意指针类型
    if (mm == MAP_FAILED)
        sys_err("mmap error");
    close(fd);

    while (1) {
        printf("id=%d\tname=%s\t%c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }
    munmap(mm, sizeof(student));
    return 0;
}
