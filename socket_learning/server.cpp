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
	return;
}
int main() {
	// 设置捕捉函数
	struct  sigaction act;
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
	struct sockaddr_in com_addr;
	socklen_t com_len = sizeof(com_addr);
	int com_fd;
	std::cout << "Accepting connections ...\n";
	while(1){
		com_fd = accept(ser_fd, (struct sockaddr*)&ser_addr, &com_len);
		pid_t pid = fork();//创建子进程
		if(pid == 0){
			close(ser_fd);
			while(1){
				char buf[BUFSIZ];
				// 读取对端发送的数据
				int len = Read(com_fd, buf, sizeof(buf));
				if(len == 0){
					std::cout << "the other side closed\n";
					break;
				}
				char cli_IP[BUFSIZ];
				std::cout << "received from " << inet_ntop(AF_INET,&com_addr.sin_addr.s_addr, cli_IP, sizeof(cli_IP)) << " at port " << ntohs(com_addr.sin_port) << std::endl;
				for(int i = 0; i < len; i++)
					buf[i] = toupper(buf[i]);
				Write(STDOUT_FILENO, buf, len);
				Write(com_fd, buf, len);
			}
			Close(com_fd);
			return 0;
		}
		else if(pid >0){
			Close(com_fd);
		}else {
			perror("fork error");
		}
	}
	return 0;
}
