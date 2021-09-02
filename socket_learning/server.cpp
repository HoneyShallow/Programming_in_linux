#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>

const unsigned short SER_PORT= 6666;
#define SER_IP "127.0.0.1"

int main(){
	/*1.建立socket*/
	int ser_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_fd == -1){
		perror("socket error");
		exit(1);
	}
	/*2.绑定ip和端口号*/
	struct sockaddr_in ser_addr;//服务器的地址+端口号
	//bzero(&ser_addr, sizeof(ser_addr));
	memset(&ser_addr,0,  sizeof(ser_addr));//将ser_addr处的所有字节填充为'\0'
	ser_addr.sin_family = AF_INET; // 地址族类型
	ser_addr.sin_port = htons(SER_PORT); // 端口号htons转变字节序
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip地址
	int ans = bind(ser_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ans == -1){
		perror("bind error");
		exit(1);
	}
	/*3.listen设置监听*/
	ans = listen(ser_fd, 128);
	if(ans == -1){
		perror("listen error");
		exit(1);
	}
	/*4.accept接受连接请求*/
	struct sockaddr_in com_addr;
	socklen_t com_len = sizeof(com_addr);
	int com_fd = accept(ser_fd, (struct sockaddr*)&com_addr, &com_len);
	if(com_fd == -1){
		perror("accept error");
		exit(1);
	}
	char com_IP[BUFSIZ];
	std::cout << "client ip:" << inet_ntop(AF_INET, &com_addr.sin_addr.s_addr, com_IP, sizeof(com_IP)) << " client port:" << ntohs(com_addr.sin_port) << std::endl;
	/*5.read读数据*/
	while(1){
		char buf[1024];
		int len = read(com_fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);
		for(int i = 0; i < len; i++)
			buf[i] = toupper(buf[i]);
		write(com_fd, buf, len);
	}
	close(ser_fd);
	close(com_fd);

	return 0;
}
