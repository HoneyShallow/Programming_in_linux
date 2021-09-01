#include <iostream>
#include <fcntl.h>
#include <unistd.h>
int main() {
	// lseek();	
	char buf[16];
	std::cout << sizeof(buf) << std::endl;
	int ret = access("./test.txt", F_OK);
	if(ret == 0)
		std::cout << "文件存在" << std::endl;
	else 
		std::cout << "文件不存在" << std::endl;
	return 0;
}
