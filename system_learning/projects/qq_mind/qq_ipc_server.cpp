#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
#include "qq_ipc.h"
#include "mylink.h"

#define SERVER_PROT "SEV_FIFO"     /*定义众所周知的共有管道*/

void sys_err(const char *str);//打印系统错误信息，返回
// 根据数据包，给出相应的操作
int login_qq(QQ_DATA_INFO *buf, mylink *head);
void transfer_qq(QQ_DATA_INFO *buf, mylink *head);
int logout_qq(QQ_DATA_INFO *buf, mylink *head);
void err_qq(QQ_DATA_INFO *buf);

mylink head = NULL;                         /*定义用户描述客户端信息的结构体*/

/*有新用户登录,将该用户插入链表*/
int login_qq(QQ_DATA_INFO *buf, mylink *head)
{
	// 服务器对于用户的私有管道只能写
    int fd = open(buf->srcname, O_WRONLY);      /*获取登录者名字,以只写方式打开以其名字命名的私有管道*/
    mylink node = make_node(buf->srcname, fd);  /*利用用户名和文件描述符创建一个节点*/
    mylink_insert(head, node);                  /*将新创建的节点插入链表*/

    return 0;
}

/*客户端发送聊天,服务器负责转发聊天内容*/
void transfer_qq(QQ_DATA_INFO *buf, mylink *head)
{
    mylink des = mylink_search(head, buf->destname); /*遍历链表查询目标用户是否在线*/
    if (des == NULL) { //目标用户不存在
        QQ_DATA_INFO lineout = {3};              /*封装3号数据包*/
        strcpy(lineout.destname, buf->destname); /*将目标用户名写入3号包*/
		// 通过私有通道回应发送源对方不在线
        mylink src = mylink_search(head, buf->srcname);   /*获取源用户节点,得到对应私有管道文件描述符*/
        write(src->fifo_fd, &lineout, sizeof(lineout));   /*通过私有管道写给数据来源客户端*/
    } else
        write(des->fifo_fd, buf, sizeof(*buf));           /*目标用户在线,将数据包写给目标用户*/
}

/*客户端退出*/
int logout_qq(QQ_DATA_INFO *buf, mylink *head)
{
    mylink p = mylink_search(head, buf->srcname); /*从链表找到该客户节点*/
    close(p->fifo_fd);                           /*关闭其对应的私有管道文件描述符*/
    mylink_delete(head, p);                     /*将对应节点从链表摘下*/
}

int main(void)
{
    if (access(SERVER_PROT, F_OK) != 0) {   
	/*判断公有管道是否存在, 不存在则创建*/
        int ret = mkfifo(SERVER_PROT, 0664);
		if(ret == -1)
			sys_err("mkfifo error\n");
    }
	int server_fd = open(SERVER_PROT, O_RDONLY);      /*公共管道文件描述符(读端)*/
    if (server_fd < 0)  /*服务器以只读方式打开公有管道一端*/
        sys_err("open error");

    mylink_init(&head);    /*初始化在线列表*/
	
    while (1) {
		QQ_DATA_INFO dbuf;           /*定义数据包结构体对象*/
        read(server_fd, &dbuf, sizeof(dbuf));    /*从公共管道中读取数据包,处理数据*/
        switch (dbuf.protocal) {
            case 1: login_qq(&dbuf, &head); break;      
            case 2: transfer_qq(&dbuf, &head); break;   
            case 4: logout_qq(&dbuf, &head); break;
            default: err_qq(&dbuf);
        }
    }

    close(server_fd);
}
void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}
void err_qq(struct QQ_DATA_INFO *buf)
{
	std::cout <<  "bad client " << buf->srcname << " connect" << std::endl;
}
