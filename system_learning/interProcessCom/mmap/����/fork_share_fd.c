/* 
 *父子进程共享打开的文件描述符------使用文件完成进程间通信.
 */
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>

// 对于借助文件的父子进程间通信，需要控制父子进程的执行顺序
int main(void)
{
    char *str = "---------父子进程共享PID测试-----\n";
    int pid = fork(); // 创建子进程
    if (pid < 0) { // 创建子进程失败
        perror("fork error");
        exit(1);
    } else if (pid == 0) { // 子进程
        int fd1 = open("test.txt", O_RDWR); // 可读可写
        if (fd1 < 0) {
            perror("open error");
            exit(1);
        }
		sleep(3);
		// 父进程先执行完，，但由于此时子进程还未写入数据到文件中
		// 那么父进程也不能读出数据，故返回的长度为0，也即直接读到文件尾
        write(fd1, str, strlen(str)); // 将字符串写入到text.txt文件中
        std::cout << "child wrote over...\n";
    } else { // 父进程
        int fd2 = open("test.txt", O_RDWR); // 可读可写
        if (fd2 < 0) {
            perror("open error");
            exit(1);
        }
       // sleep(1);   //保证子进程写入数据
		char buf[1024];	// 父进程读出文件数据并打印到屏幕上
        int len = read(fd2, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        wait(NULL); // 等待回收子进程
    }

    return 0;
}
