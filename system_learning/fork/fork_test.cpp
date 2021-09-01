#include <iostream>
#include <unistd.h>
#include <typeinfo>
int main() {
	using namespace std;
	pid_t pid;
	std::cout << "vxxxxxxx\n";
	// cout << typeid(pid_t).name() << endl;
	int i;
	/*
	 * 当i=0时,调用fork生成一个进程，而for循环相当于是不同i是的顺序语句也就是从当前fork开始往后的语句这个进程均会执行，那么从i=0到i=4一共执行了5层代码，当i++后，从i=1开始会执行4层代码，以此类推，最终会得到2^5-1个进程，显然不是我们想要的结果，那么我们就需要在i处成功产生子进程时就终止循环的后续语句，也即借助break终止循环
	 * */
	for(i = 0; i < 5; i++){
		pid = fork();
		// fork原理：父进程执行全部代码，fork创建的子进程仅执行fork以后的代码，而由程序创建的父进程的父进程是bash
		if(pid == -1){
			perror("fork error");
			exit(1);
		} else if (pid == 0){
			break;
			// cout << "第" << i+1 << "child:" << getpid() << "父进程" << getppid() << endl;
		//	sleep(1);
		} else{
		//	cout << "parent:" << getpid() << "父进程" << getppid() << endl;
		}
	}
	if(i < 5){
		sleep(i);
		cout << i+1 << "child " << "pid = " << getpid() << endl;
	}else {
		sleep(i);
		cout << "parent" << endl;
	}
	//如果按照上边的做法，最终会创建出来2^n-1个子进程
	// cout << "YYYYYYY\n";
	return 0;
}
