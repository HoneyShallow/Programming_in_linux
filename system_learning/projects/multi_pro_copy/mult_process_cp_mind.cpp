#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main()
{   
	using namespace std;
    //1. 指定创建子进程的个数
	int pro_num;
	cout << "指定可利用的进程个数: ";
	cin >> pro_num;

    //2. 打开源文件
	// 对于源文件，我们只进行读取操作
    int fd_s = open("dict.txt", O_RDONLY);
	if(fd_s < 0) 
		sys_err("open source file failed\n");
    //3. 打开目的文件, 不存在则创建
	int fd_d = open("target.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if(fd_d < 0) 
		sys_err("open target file failed\n");
    //4. 获取文件大小
    int len = lseek(fd_s, 0, SEEK_END);
    //5. 根据文件大小拓展目标文件
    ftruncate(fd_d, len);
    //6. 为源文件创建映射
    char * mm_s = (char *)mmap(NULL, len, PROT_READ, MAP_SHARED, fd_s, 0);
	if(mm_s == MAP_FAILED)
		sys_err("mmap source failed\n");
    //7. 为目标文件创建映射
    char * mm_d = (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_d, 0);
	if(mm_d == MAP_FAILED)
		sys_err("mmap target failed\n");
	// 建立映射后关闭文件
	close(fd_s);
	close(fd_d);
	
    //8. 求出每个子进程该拷贝的字节数
	int normal_pro_bits = len / pro_num;
	int last_pro_bits = normal_pro_bits + len % normal_pro_bits;
	
    //9. 创建N个子进程
	int i;
	for(i = 0; i < pro_num; i++){
		pid_t pid = fork();
		if(pid == 0)
			break;
		else if(pid == -1) 
			sys_err("fork failed\n");
	}
	
    //10. 子进程完成分块拷贝(注意最后一个子进程拷贝起始位置)
	if(i < pro_num){// 子进程
		if(i == pro_num-1)
			memcpy(mm_d + i * normal_pro_bits, mm_s + i * normal_pro_bits, last_pro_bits);
		else
			memcpy(mm_d + i * normal_pro_bits, mm_s + i * normal_pro_bits, normal_pro_bits);
		// 将源映射区中的数据拷贝到目标映射区
	}else {// 父进程
		// 回收子进程
		for(int i = 0; i < pro_num; i++)
			wait(NULL);
	}
    //11. 释放映射区
	munmap(mm_s, len);
	munmap(mm_d, len);
    return 0;
}
