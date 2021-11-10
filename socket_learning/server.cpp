#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <sys/wait.h>
#include <signal.h>

#include "wrap.h"
const unsigned short SER_PORT = 8888;
#define SER_IP "127.0.0.1"

void wait_child(int signo){
	while(waitpid(0, NULL, WNOHANG));
	//此处不能使用if，是因为在回收某个进程时，有可能其他进程也子进程也结束了，那么我们此时也就需要一同将其回收
	return;
}
int main() {
	// 设置捕捉函数回收子进程
	struct sigaction act;
	act.sa_handler = wait_child;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;	
	sigaction(SIGCHLD, &act, NULL);

	// 1.创建socket文件描述符，指定地址族类型为ipv4,采用TCP协议
	int ser_fd = Socket(AF_INET, SOCK_STREAM, 0);
	// 2.绑定sock文件描述符和地址
	struct sockaddr_in ser_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SER_PORT);
	inet_pton(AF_INET, SER_IP, &ser_addr.sin_addr.s_addr);
	Bind(ser_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	// 3.设置监听数量
	Listen(ser_fd, 128);
	// 4.接受客户端连接请求
	int com_fd;
	std::cout << "Accepting connections ...\n";
	while(1){
		struct sockaddr_in com_addr;
		socklen_t com_len = sizeof(com_addr);
		com_fd = accept(ser_fd, (struct sockaddr*)&ser_addr, &com_len);
		pid_t pid = fork();//创建子进程
		if(pid == 0){// 子进程负责通过通信socket完成数据交互
			// 而无需再接收客户端的发送请求，所以关闭
			Close(ser_fd);
			// 读取客户端发送的数据
			while(1){
				char buf[BUFSIZ];
				int len = Read(com_fd, buf, sizeof(buf));
				// 打印客户端的信息
				char cli_IP[BUFSIZ];
				std::cout << "received from " << inet_ntop(AF_INET,&com_addr.sin_addr.s_addr, cli_IP, sizeof(cli_IP)) << " at port " << ntohs(com_addr.sin_port) << std::endl;
				if(len == 0){
					std::cout << "the other side closed\n";
					break;
				}
				// 将未处理的数据打印到屏幕上
				Write(STDOUT_FILENO, buf, len);
				for(int i = 0; i < len; i++)
					buf[i] = toupper(buf[i]);
				// 将处理完的数据发送给客户端
				Write(com_fd, buf, len);
			}
			// 跳出循环说明客户端已经不再发送数据，那么该通信socket也就没有存在的必要了
			Close(com_fd);
			return 0;// 子进程结束
		}else if(pid > 0){// 父进程不需要交互数据，所以关闭通信socket
			Close(com_fd);
		}else {
			perror("fork error");
		}
	}
	return 0;
}
