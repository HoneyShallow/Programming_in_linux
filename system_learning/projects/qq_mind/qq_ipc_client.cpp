#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "qq_ipc.h"
#include "mylink.h"

#define SERVER_PROT "SEV_FIFO"

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) { // 客户端的运行格式
	    std::cout << "./client name\n";
        exit(1);
    }
	int server_fd = open(SERVER_PROT, O_WRONLY);
    if (server_fd < 0)  /*客户端只写打开公共管道*/
        sys_err("open error");

    mkfifo(argv[1], 0777);     /*为本客户创建专享的管道*/

    QQ_DATA_INFO cbuf;

    cbuf.protocal = 1;       /*1号包表登录包*/
    strcpy(cbuf.srcname,argv[1]);   /*按既定设计结构,将登录者(自己的名字)写入包结构中*/
    int client_fd = open(argv[1], O_RDONLY|O_NONBLOCK);  /*只读打开私有管道,修改私有管道的属性为非阻塞*/

	/*设置标准输入缓冲区的读写为非阻塞*/
    int flag = fcntl(STDIN_FILENO, F_GETFL);    
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);

    write(server_fd, &cbuf, sizeof(cbuf));  /*向公共管道中写入"登录包"数据,表示客户端登录*/

    while (1) {
		QQ_DATA_INFO tmpbuf; // 对方响应的数据包
        int len = read(client_fd, &tmpbuf, sizeof(tmpbuf));     /*读私有管道*/
        if (len > 0) {
            if (tmpbuf.protocal == 3)  /*服务器相应对方不在线*/
                std::cout << tmpbuf.destname << "is not online\n";
            else if (tmpbuf.protocal == 2)  /*对方在线,显示对方对自己说的话*/
                std::cout << tmpbuf.srcname << ": " << tmpbuf.data << std::endl;
        } else if (len < 0) { // 读错误
            if (errno != EAGAIN)
                sys_err("client read error");
        }
		char cmdbuf[256];
		QQ_DATA_INFO talkbuf; // 自身回应的数据包
        len = read(STDIN_FILENO, cmdbuf, sizeof(cmdbuf));   /*读取客户端用户输入*/
        if (len > 0) {
            memset(&talkbuf, 0, sizeof(talkbuf));  /*将存储聊天内容的缓存区清空*/
            cmdbuf[len] = '\0';          /*填充字符串结束标记*/
            // destname#
			// data
            //B#你好
            char* dname = strtok(cmdbuf, "#\n");  /*按既定格式拆分字符串*/
            
            if (strcmp("exit", dname) == 0) {    /*退出登录:指定包号,退出者名字*/
                talkbuf.protocal = 4;
                strcpy(talkbuf.srcname, argv[1]);
                write(server_fd, &talkbuf, sizeof(talkbuf));
				/*将退出登录包通过公共管道写给服务器*/
                break;
            } else {
                talkbuf.protocal = 2;             /*聊天*/
                strcpy(talkbuf.destname, dname);  /*填充聊天目标客户名*/
                strcpy(talkbuf.srcname, argv[1]); /*填充发送聊天内容的用户名*/

                char* databuf = strtok(NULL, "\0");               
                strcpy(talkbuf.data, databuf);
				write(server_fd, &talkbuf, sizeof(talkbuf)); /*将聊天包写入公共管道*/
            }
        }
    }
	// 如果执行到此处，说明用户已退出，收回用户使用的资源
    unlink(argv[1]);            /*删除私有管道*/
    close(client_fd);           /*关闭私有管道的读端(客户端只掌握读端)*/
    close(server_fd);           /*关闭公共管道的写端(客户端值掌握写端)*/

    return 0;
}
