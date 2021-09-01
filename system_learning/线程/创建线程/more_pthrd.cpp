#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
void *tfn(void *arg)
{
	//int i = *((int*)arg);
	long i = (long)arg;
	sleep(i);	 //通过i来区别每个线程
	std::cout << "In thread #" << i << "thread id = " << pthread_self()
			<< ",process id = " << getpid() << std::endl;
	return NULL;
}

int main(int argc, char *argv[])
{
	int n = 5;
	pthread_t tid;
	// 默认创建线程数是5，如果又传入参数，则按照传入参数为标准
	if (argc == 2)
		n = atoi(argv[1]);

	for (long i = 0; i < n; i++) {
		//int ret = pthread_create(&tid, NULL, tfn, (void *)&i);
		int ret = pthread_create(&tid, NULL, tfn, (void *)i);
		if(ret != 0){
			std::cout << strerror(ret) << std::endl;
			exit(1);
		}
		//将i转换为指针，在tfn中再强转回整型。
	}
	sleep(n);
	std::cout << std::endl;
	std::cout << "In thread:thread id = " << pthread_self()
			<< ",process id = " << getpid() << std::endl;
	return 0;
}
