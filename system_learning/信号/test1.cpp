#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
void do_wait(int signo){
	pid_t pid;
	int status;
	while((pid = waitpid(0, &status, WNOHANG)) > 0){
		if(WIFEXITED(status))
			std::cout << "child exit with " << WEXITSTATUS(status)<< std::endl;
		if(WIFSIGNALED(status))
			std::cout << "child killed by " << WTERMSIG(status) << std::endl;
	}
}
void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main() {
	int fd[2]; // fd[0]读，fd[1]写
	int ret = pipe(fd);// 构建管道
	if (ret == -1)
		sys_err("pipe error");
	pid_t  pid = fork(); // 创建子进程
	if(pid == -1){
		sys_err("fork error");
	}else if(pid > 0){
		//signal(SIGCHLD, do_wait);
		//照常执行下边的语句，而当子进程结束后回收子进程
		//如果直接在父进程采用wait回收，由于execl的特性可知在执行
		//完命令后不会再返回父进程了，导致wait无效
		//而采用捕捉函数当捕捉到信号时，内核会完成处理操作从而回收子进程
		struct sigaction act;
		act.sa_handler = do_wait;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;

		sigaction(SIGCHLD, &act, NULL);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);//
		execl("/bin/ls", "ls", "-l", NULL);
	} else{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}
