#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>

#include "wrap.h"
#define SERV_PORT 6666

int main(void)
{
    struct sockaddr_in serv_addr;

    int sfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));           
    serv_addr.sin_family = AF_INET;                 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听本地所有ip
    serv_addr.sin_port = htons(SERV_PORT);          

    Bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    Listen(sfd, 2);                                

    printf("wait for client connect ...\n");

	struct sockaddr_in clie_addr;
    socklen_t clie_addr_len = sizeof(clie_addr_len);
    int cfd = Accept(sfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
    printf("cfd = ----%d\n", cfd);

	char clie_IP[BUFSIZ];
    printf("client IP: %s  port:%d\n", 
            inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_IP, sizeof(clie_IP)), 
            ntohs(clie_addr.sin_port));

    while (1) {
		char buf[BUFSIZ]; // 读取对方发送的数据并打印到屏幕上
        int len = Read(cfd, buf, sizeof(buf));
        Write(STDOUT_FILENO, buf, len);

        for (int i = 0; i < len; i++) // 处理数据
            buf[i] = toupper(buf[i]);
        Write(cfd, buf, len);  // 将处理结果回应给客户端
    }

    Close(sfd);
    Close(cfd);

    return 0;
}
