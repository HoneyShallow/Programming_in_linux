#include <iostream>
#include <sys/time.h>
#include <signal.h>

void myfunc(int signo)
{
	std::cout << "hello world\n";
    //	raise(SIGALRM);//如果这行代码不注释掉，会导致在第一次调用捕捉函数之后递归调用该函数， 
}

int main(void)
{
	struct itimerval it, oldit;
	signal(SIGALRM, myfunc);   //注册SIGALRM信号的捕捉处理函数。

	it.it_value.tv_sec = 5;// 存在默认的时间起点0.0，此处设置了第一个闹钟时间
	it.it_value.tv_usec = 0;//这里则是设置了相邻两个闹钟之间相差的时间

	it.it_interval.tv_sec = 3;
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &it, &oldit) == -1){
		perror("setitimer error");
		return -1;
	}

	while(1);

	return 0;
}
