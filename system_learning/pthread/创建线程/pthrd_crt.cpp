#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

void *tfn(void *arg)
{
	std::cout << "In thread:thread id = " << pthread_self()
			<< ",process id = " << getpid() << std::endl;
	return NULL;
}

int main(void)
{
	pthread_t tid;
	std::cout << "In main1:thread id = " << pthread_self() 
			<< ",process id = " << getpid() << std::endl;
	// 采用默认属性，执行tfn函数
	int ret = pthread_create(&tid, NULL, tfn, NULL);
	if(ret != 0){
		std::cout << strerror(ret) << std::endl;
		exit(1);
	}
	sleep(1); // 主控线程需要等待子线程打印输出
		std::cout << "In main2:thread id = " << pthread_self()
			<< ",process id = " << getpid() << std::endl;

	return 0;
}
