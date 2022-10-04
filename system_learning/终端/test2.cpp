#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
void daemond();

void daemond(){
	pid_t pid = fork();
	if(pid < 0){
		perror("fork failure");
		exit(1);
	}else if(pid > 0){
		exit(0);
	}
	//创建会话
	setsid();
	//修改当前工作路径
	int ret = chdir("/home/linux");
	if(ret == -1){
		perror("chdir failure");
		exit(1);
	}
	//修改掩码
	umask(0022);
	//关闭0,1,2三个文件描述符
	close(STDIN_FILENO);
	open("/dev/null",O_RDWR);
	dup2(0, 1);
	dup2(0, 2);
}

int main(){
	daemond();
	while(1){
		execl("/bin/ls", "date", NULL);
		sleep(1);
	}
	return 0;
}
