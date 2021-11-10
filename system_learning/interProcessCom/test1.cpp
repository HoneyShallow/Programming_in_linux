/*
 * 先执行,将数据写入文件test.txt
 */
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#define N 5

int main(void)
{
    // 如果文件不存在，创建；如果文件存在但不为空，清空文件
    int fd = open("test.txt", O_RDWR|O_TRUNC|O_CREAT, 0664);
    const  char *str = "--------------secesuss-------------\n";
    //直接打开文件写入数据
    write(fd, str, strlen(str));
    std::cout << "test1 write into test.txt finish\n";

    sleep(N);// 等待进程test2完成操作

    lseek(fd, 0, SEEK_SET); // 重置文件指针为0，也即位于文件头
    char buf[1024];
    int ret = read(fd, buf, sizeof(buf));
    ret = write(STDOUT_FILENO, buf, ret);
    // 读取test2写入的数据并打印到屏幕上
    if (ret == -1) {
        perror("write second error");
        exit(1);
    }
    close(fd);
    return 0;
}
