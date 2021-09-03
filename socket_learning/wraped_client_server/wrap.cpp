#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

void perr_exit(const char *s)
{
	perror(s);
	exit(-1);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n = accept(fd, sa, salenptr);
again:
	if (n < 0) {
		if ((errno == ECONNABORTED) || (errno == EINTR))
			goto again;
		else
			perr_exit("accept error");
	}
	return n;
}

int Bind(int fd, const struct sockaddr *sa, socklen_t sa_len)
{
    int n = bind(fd, sa, sa_len);

    if (n < 0) 
	perr_exit("bind error");

    return n;
}

int Connect(int fd, const struct sockaddr *sa, socklen_t sa_len)
{
    int n = connect(fd, sa, sa_len);
    if (n < 0)
		perr_exit("connect error");
    return n;
}

int Listen(int fd, int backlog)
{
    int n = listen(fd, backlog);
    if (n < 0) 
		perr_exit("listen error");

    return n;
}

int Socket(int family, int type, int protocol)
{
	int n = socket(family, type, protocol);
	if (n < 0)
		perr_exit("socket error");

	return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n = read(fd, ptr, nbytes);
again:
	if (n == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n = write(fd, ptr, nbytes);
again:
	if (n == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}

int Close(int fd)
{
    int n = close(fd);
	if (n == -1)
		perr_exit("close error");
    return n;
}

 /*参三: 应该读取的字节数*/         
//socket 4096  readn(cfd, buf, 4096)   nleft = 4096-1500
ssize_t Readn(int fd, void *vptr, size_t n)
{
	size_t nleft = n;            //usigned int 剩余未读取的字节数
	ssize_t nread;              //int 实际读到的字节数
	char *ptr = (char *)vptr;

	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		} else if (nread == 0) // 说明读到文件尾了，没有必要再继续读下去
			break;

		nleft -= nread;   //下次再读取时，剩余字节数减少
		ptr += nread; // 读取指针位置前进
	}
	return n - nleft; // 返回已读取的字节数
}

ssize_t Writen(int fd, const void *vptr, size_t n)
{
	size_t nleft = n; // 表示剩余要写入的字节数
	ssize_t nwritten; // 表示已经写入的字节数
	const char *ptr = (const char *)vptr;

	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}
/*
static ssize_t my_read(int fd, char *ptr)
{
	static int read_cnt; // 设置为static表示记录每次修改后的值
	static char *read_ptr;
	static char read_buf[100];

	if (read_cnt <= 0) {
again:
		// 从对端读取数据到buf中，
		read_cnt = read(fd, read_buf, sizeof(read_buf))；
		if (read_cnt < 0) {  
			//"hello\n"
			if (errno == EINTR)	goto again;
			else 		return -1;
		} else if (read_cnt == 0) // 读到对端结尾了，返回0表示读完了
			return 0;

		read_ptr = read_buf;
	}
	// 表示上次从到缓冲区中的数据还没处理完，接着往后处理
	read_cnt--;
	*ptr = *read_ptr++; //ptr为读取到数据的第一个字符

	return 1;
}

readline --- fgets
//传出参数 vptr
ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t rc;
	char c, *ptr = vptr;

	for (ssize_t n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c)) == 1) {   //ptr[] = hello\n
			*ptr++ = c; // 如果读到\n就说明已经读够一行数据
			if (c == '\n')
				break;
		} else if (rc == 0) { // 表示在该字符串中没有出现\n,且已经读到对端末尾了
			*ptr = 0; // 将最后的字符设置为字符串结尾标志
			return n-1;
		} else
			return -1;
	}
	*ptr = 0; // 字符串中出现了\n,直接从此处将字符串截断，在读到的数据结尾添加字符串结束标志

	return n;
}
*/
