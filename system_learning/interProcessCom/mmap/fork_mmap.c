#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int var = 100;
/*
父子间进程通信步骤：
1.父进程先创建映射区：open(), mmap() close()
2.指定MAP_SHARED权限
3.fork创建子进程
4.一个进程读，一个进程写
共享结果：
child *p = 2000, var = 1000 
parent *p = 2000, var = 100 
私有结果：
child *p = 2000, var = 1000 
parent *p = 0, var = 100 
*/
int main(void)
{
	// 1.构建映射区
    int fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    unlink("temp");	//删除临时文件目录项,使之具备被释放条件.
    ftruncate(fd, 4);

    // int* p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    // int* p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	// 如果是共有，父子进程使用的是内核中同一片映射区
	// 如果是私有，父进程独享映射区，子进程只拥有初始化的映射区，相当于深拷贝
	// 重新为其分配了另外一份映射区，此时子进程对其映射区的修改并不回影响到父进程的的映射区
    if(p == MAP_FAILED){		//注意:不是p == NULL
        perror("mmap error");
        exit(1);
    }
    close(fd);	//映射区建立完毕,即可关闭文件

	// 2.创建子进程
    pid_t pid = fork();				
    if(pid == 0){ // 子进程
        *p = 2000;		// 写共享内存
        var = 1000; // 读时共享写时复制
		//	共享内存的地址位于knerl区，子进程和父进程有相同的映射区地址
		// 指向相同的空间，所谓一荣俱荣，一损皆损
		// 而全局变量位于用户区，子进程和父进程有各自的存储位置，互不影响
        std::cout << "child " << "*p = " << *p << ", var = " << var << endl;
    } else { // 父进程
        sleep(1);
		// 读共享内存
        std::cout << "parent " << "*p = " << *p << ", var = " << var << endl;
        wait(NULL); //回收子进程
		
		//释放映射区
        int ret = munmap(p, 4);				
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    }

    return 0;
}
