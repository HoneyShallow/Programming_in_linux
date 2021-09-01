#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <string>
void sys_err(const char* str){
	perror(str);
	exit(1);
}
int main(){
	const char * fifoname = "fifoname";
	int ret = mkfifo(fifoname,0664);
	if(ret == -1)
		sys_err("mkfifo error");
	int fd = open(fifoname, O_WRONLY);
	if(fd == -1)
		sys_err("open error");
	int i = 0;
	while(1){
		// char buf[4096];
		// int len = std::cin.getline(buf, 4096); 
		std::string buf = "hello you ";
		buf += std::to_string(i++);
		std::cout << buf << std::endl;
		write(fd, buf.c_str(), strlen(buf.c_str()));
		sleep(1);
	}
	return 0;
}

