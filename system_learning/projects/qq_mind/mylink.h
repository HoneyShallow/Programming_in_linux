#ifndef _MYLINK_H_
#define _MYLINK_H_
#include <cstring>
#include <iostream>
typedef struct node *mylink;
struct node {
	char item[20];  //记录客户端名字（用户端/服务器端）
    int fifo_fd;    //该客户端使用的私有管道文件描述符(写端)，专享管道
	mylink next;	//struct node *next;
};

void mylink_init(mylink *head); // 初始化
mylink make_node(char *name, int fd); // 构造节点
void mylink_insert(mylink *head, mylink p); // 将目标插入在线列表
mylink mylink_search(mylink *head, char *keyname);// 查询目标是否在线
void mylink_delete(mylink *head, mylink p); // 删除目标同时释放空间
// void free_node(mylink p); // 释放结点空间
void mylink_destory(mylink *head); // 销毁整个在线列表
void mylink_travel(mylink *head, void (*vist)(mylink)); // 遍历在线列表

#endif
