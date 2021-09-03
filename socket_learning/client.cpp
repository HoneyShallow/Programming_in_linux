#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "wrap.h"

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

int main(void)
{
    struct sockaddr_in serv_addr;

    int sfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));                       
    serv_addr.sin_family = AF_INET;     // 地址族类型                        
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);    //设置ip
    serv_addr.sin_port = htons(SERV_PORT);   // 设置端口                   

    Connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {
		char buf[BUFSIZ]; 
        fgets(buf, sizeof(buf), stdin);
        int r = Write(sfd, buf, strlen(buf)); //从标准输入读取数据发送给服务器      
        printf("Write r ======== %d\n", r);  // 打印发送的数据量
        int len = Read(sfd, buf, sizeof(buf)); //读取服务器响应的数据
        printf("Read len ========= %d\n", len); // 打印对方回应的数据量
        Write(STDOUT_FILENO, buf, len);	//打印到屏幕上
    }

    Close(sfd);

    return 0;
}

