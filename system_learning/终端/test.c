#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
void test01(){
	int ret = chdir("~/system_learning/opgg");
	if(ret == -1){
		perror("chdir error");
		exit(1);
	}
// 	execlp("pwd", "pwd", NULL);

}
int main() {
	using std::cout;
	using std::endl;
	test01();
	// cout << ttyname(0) << endl;
	// cout << ttyname(1) << endl;
	// cout << ttyname(2) << endl;
	return 0;

}
