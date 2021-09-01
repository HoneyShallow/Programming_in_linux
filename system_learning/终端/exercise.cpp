#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
void do_work(int);
void mydaemond();

void do_work(int signo){
	int fd = open("./spec.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
	if(fd == -1){
		perror("open failed");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	execlp("date", "date", NULL);
	close(fd);
}

void mydaemond() {
	//1.创建子进程
	pid_t pid =fork();
	if(pid > 0){//父进程直接退出
		exit(1);
	}else if(pid == -1){
		perror("fork error");
		exit(1);
	}
	// 2.为该进程创建会话
	setsid();
	// 3.改变工作路径
	int ret = chdir("/home/linux/");
	if(ret == -1){
		perror("chdir error");
		exit(1);
	}
	// 4.改变文件权限
	umask(0022);
	// 5.关闭文件描述符
	close(STDIN_FILENO);
	open("/dev/null", O_RDWR);
	dup2(0, STDOUT_FILENO);
	dup2(0, STDERR_FILENO);
	// 6.核心任务
	// 注册捕捉函数
	struct sigaction act, old_act;
	act.sa_handler = do_work;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &old_act);

}
void test01(){
	// 注册捕捉函数
	/*struct sigaction act, old_act;
	act.sa_handler = do_work;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &old_act);
	alarm(3);
	*/
	while(1){//每隔3s打印当前系统时间到指定文件中
		//alarm(3);
		//alarm(0);
		//sigaction(SIGALRM, &old_act, NULL);
		 do_work(0);
	}
}
int main() {
	test01();
	// mydaemond();
	return 0;
}
