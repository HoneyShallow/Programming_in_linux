#include <iostream>
#include <unistd.h>
int main() {
	using namespace std;
	pid_t pid = fork();
	if(pid == -1){
		perror("fork failure");
		exit(1);
	}else if(pid == 0) {
		// execlp("ls", "ls", "-a", "-l", NULL);
		// execl("/bin/ls", "ls", "-a", "-l", NULL);
		// 上边两行代码的效果相同，区别就在于execlp使用的是程序名，而execl使用的是程序所在的绝对路径，后边的命令行参数相同
		// if(execl("/home/linux/system_learning/exec/while", "while", NULL) < 0)
		/*
		if(execl("./while", "while", NULL) < 0)
			cout << "error" << endl;
		else 
			cout << "success." << endl;
		execl可以调用自定义可执行程序，execlp只能调用系统可执行程序
		 */
	//	char* argv[6] = {"ls", "-l", "-a", "-h", NULL};
		char* argv[] = {"ls", "-l", "-a", "-h", NULL};
		execv("/bin/ls", argv);
		execvp("ls", argv);
	}else {
		sleep(1);
		cout << "parent\n";
	}
	return 0;
}
