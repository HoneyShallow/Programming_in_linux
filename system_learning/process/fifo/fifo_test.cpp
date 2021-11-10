#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
int main() {
	int ret = mkfifo("mytestfifo",0664);
	if(ret == -1){
		perror("mkfifo error");
		exit(1);
	}	
	return 0;
}

