#include <iostream>
#include <unistd.h>
int val = 55;

int main(int argc, char **argv){
	using std::endl;
	using std::cout;
	int n = atoi(argv[1]); // 将输入参数转为整形
	int i;
	for(i = 0; i < n; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			exit(1);
		}else if(pid == 0){
			break;
		}
	}
	if(i < n){
		val = 200;
		cout << "var = " << val << endl;
	}
	else if(i == n){
		sleep(1);
		val = 100;
		cout << "var = " << val << endl;
	}
	cout << "var = " << val << endl;
	return 0;
}
