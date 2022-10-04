#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t s;//定义一个信号量

void *func(void *arg){
	char data[1024];

	while(1){
		int ret = read(STDIN_FILENO, data, 1024);
		// 从输入缓冲区中读取数据，如果没有数据阻塞，如果有数据，返回读到的字节数
		// 一旦读到数据
		if(ret > 0){
			sem_post(&s);
		}
	}
	return NULL;
}
int main(){
	pthread_t tid;
	// 创建一个线程
	pthread_create(&tid, NULL, func, NULL);
	//初始化信号量
	sem_init(&s, 0, 0);
	struct timespec t = {0, 0};
	t.tv_sec = time(NULL);
	t.tv_nsec = 0;
	while(1){
		sem_timedwait(&s, &t); // 初始时直接打印
		std::cout << "hello world\n" << std::endl;
		//随后每隔5s打印一次
		//如果在5s内信号量可用了，就会直接打印，否则需要等待5s才能打印
		t.tv_sec = time(NULL) + 5;
		t.tv_nsec = 0;
	}
	return 0;
}
