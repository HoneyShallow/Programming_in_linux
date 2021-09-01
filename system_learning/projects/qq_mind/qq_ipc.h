#ifndef QQ_IPC_H
#define QQ_IPC_H

struct QQ_DATA_INFO {
    int protocal; 	// 协议号
    char srcname[20]; // 信号的发送方
    char destname[20]; // 信号的接收方
    char data[100]; // 传输的数据
};

/*
 * protocal     srcname      destname      data
 * 1            登陆者       NULL
 * 2            发送方       接收方         数据
 * 3            NULL(不在线)
 * 4            退出登陆用户（退出登陆）
 */

#endif
