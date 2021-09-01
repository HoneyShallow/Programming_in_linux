#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>

const int T_NUM = 5;
const int ITEMS = 50;
char *s, *d; // 保存源文件和目标文件的映射区首地址
int *done; // 保存每个线程需要拷贝的字节数
int n = T_NUM; // 默认条件下，使用的子进程数

struct arg_t{ // 保存每个线程要完成拷贝信息和自身的信息
	int off, size, t_no;
};
void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

void err_usr(const char *str)
{
	fputs(str, stderr);
	exit(1);
}

void *tfn(void *arg)
{
	arg_t *arg_p = (arg_t *)arg;//获取该线程的拷贝任务信息
	char* p = s + arg_p->off;
	char* q = d + arg_p->off;
	for(int i = 0; i < arg_p->size; i++)
	{
		/* 逗号表达式的使用技巧*/
		*q++ = *p++, done[arg_p->t_no]++;
		usleep(10);
	}
	return NULL;
}

void *display(void *arg)
{
	long size = (long)arg;
	int interval = size / (ITEMS - 1);
	int draw = 0;
	
	while(draw < ITEMS){
		int sum = 0;// sum保存的是某个时刻各线程总共拷贝的字节数
		for(int i = 0; i < n; i++)
			sum += done[i];
		int j = sum / interval + 1;//计算当前已拷贝的字节数需要打印什么样的进度
		for(; j > draw; draw++){
			// std::cout << '='; 
			putchar('=');
			//fflush(stdout);// :刷新缓冲区
		}
	}
	putchar('\n');

	return NULL;
}

int main(int argc, char *argv[])
{
	// 1.提取参数信息
	// cp程序使用的格式： cp src des thread_num
	if(argc != 3 && argc != 4)
		err_usr("usage : cp src dst [thread_num]\n");
	if(argc == 4)
		n = atoi(argv[3]);  
	
	// 2.打开目的文件和源文件
	int src = open(argv[1], O_RDONLY); // 源文件只读权限即可
	if(src == -1)
		err_sys("fail to open src"); 
	int dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	// 目标文件则需可读可写，这是因为在建立映射是隐含需要使用读权限
	if(dst == -1)
		err_sys("fail to open des");
	
	struct stat statbuf; //获取源文件的信息并保存在statbuf中，主要是文件字节数
	if(fstat(src, &statbuf) == -1) 
		err_sys("fail to stat");

	lseek(dst, statbuf.st_size - 1, SEEK_SET);
	write(dst, "a", 1);         //IO操作拓展文件大小,也可以使用truncate
	// 3. 建立映射
	s = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, src, 0);
	if(s == MAP_FAILED)
		err_sys("fail to mmap");
	d = (char *)mmap(NULL, statbuf.st_size, PROT_WRITE , MAP_SHARED, dst, 0);
	if(d == MAP_FAILED)
		err_sys("fail to mmap");
	close(src);
	close(dst);
	
	//4.为现成的要使用的公共资源申请空间
	 // 申请空间保存线程id，最后一个用于保存拷贝的进度信息
	pthread_t *tid = new pthread_t[n+1];
	// tid = (pthread_t *)malloc(sizeof(pthread_t) * (n + 1));
	if(tid == NULL)
		err_sys("fail to malloc");
	
    //记录每个线程需要拷贝字节数
	done = new int[n];
	//done = (int *)calloc(sizeof(int), n);
	if(done == NULL)
		err_sys("fail to malloc");
	
    //每个线程的任务
	arg_t *arr = new arg_t[n];
	if(arr == NULL)
		err_sys("fail to malloc");

    //构建线程任务数组，分配任务
	int len = statbuf.st_size / n, off = 0;
	for(int i = 0; i < n; i++, off += len) {
		arr[i].off = off; // 拷贝的起始位置
		arr[i].size = len;// 需要拷贝的字节数
		arr[i].t_no = i;  // 完成拷贝任务的线程号
	}
		
	arr[n - 1].size += (statbuf.st_size % n); // 多余的字节有最后一个线程完成拷贝
    
    // 创建执行拷贝任务线程
	for(int i = 0; i < n; i++)
		pthread_create(&tid[i], NULL, tfn, (void *)&arr[i]);

    // 创建进度线程
	pthread_create(&tid[n], NULL, display, (void *)statbuf.st_size);
	// 等待回收子进程
	for(int i = 0; i < n + 1; i++)
		pthread_join(tid[i], NULL);
#if 1 
	// 解除映射
	munmap(s, statbuf.st_size);
	munmap(d, statbuf.st_size);
#endif
	// 释放在堆区申请的空间
	delete [] tid;
	delete [] done;
	delete [] arr;
	return 0;
}

/*
struct stat {
   dev_t     st_dev;          ID of device containing file 
   ino_t     st_ino;          inode number
   mode_t    st_mode;         file type and mode 
   nlink_t   st_nlink;        number of hard links 
   uid_t     st_uid;          user ID of owner 
   gid_t     st_gid;          group ID of owner 
   dev_t     st_rdev;         device ID (if special file) 
   off_t     st_size;         total size, in bytes 
   blksize_t st_blksize;      blocksize for filesystem I/O 
   blkcnt_t  st_blocks;       number of 512B blocks allocated 

   struct timespec st_atim;   time of last access 
   struct timespec st_mtim;   time of last modification 
   struct timespec st_ctim;   time of last status change 
	#define st_atime st_atim.tv_sec       Backward compatibility 
	#define st_mtime st_mtim.tv_sec
	#define st_ctime st_ctim.tv_sec
};
*/
