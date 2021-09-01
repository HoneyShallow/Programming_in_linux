#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main(){
	const char * fifoname = "fifoname";
	int fd = open(fifoname, O_RDONLY);
	if(fd == -1)
		sys_err("open error");
	while(1){
		char buf[4096];
		int len = read(fd, buf, sizeof(buf)); 
		write(STDOUT_FILENO, buf, len);
		std::cout << std::endl;
		sleep(3);
	}
	return 0;
}

