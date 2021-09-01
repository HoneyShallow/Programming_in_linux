#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void sys_err(const char* );

void sys_err(const char * str){
	perror(str);
	exit(1);
}
void test01() {
	/*
	int ret = kill(getpid(), SIGKILL);
	if(ret == -1)
		std::cout << "kill fork\n";
	return 0;
	*/
}
void test02() {
	int i;
	pid_t spec_pro;
	raise(SIGSEGV);
	abort();

	for(i = 0; i < 5; i++){
		pid_t pid = fork();
		if(pid == 0) break;
		else if(pid == -1) sys_err("fork failed\n");
		if(i == 2)
			spec_pro = pid;
	}
	if(i < 5){
		while(1){
			std::cout << "I'm child" << i+1 << "pid = " << getpid() << std::endl;
			sleep(1);
		}
	}else {
		sleep(1);
		kill(spec_pro, SIGKILL);
		for(int j = 0; j < 5; j++)
			wait(NULL);
	}
}
void test03() {
	alarm(1);
	int i = 0;
	while(++i) {
		std::cout << i << std::endl;
	}
}
int main() {
	test03();
	return 0;
}
