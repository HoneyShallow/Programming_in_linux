#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void test01() {
	// char input[100] = "ps aux | grep init";
	char input[100] = "ps aux";
	char * token = std::strtok(input,  "|");

	while(token != NULL){
		std::cout << token << std::endl;
		token = std::strtok(NULL,  "|");
	}
}
void test02()
{
	//char* argv1[] = {"ls", "ls", "-l", NULL};
	char* argv1[] = {"ls", "-l", (char*)0};
	execvp(argv1[0], argv1);
	std::cout << "execv failed\n";
	/*
	int i;
	for(i = 0; i < 2; i++){
		pid_t pid = fork();
		if(pid == 0)break;
		else if(pid == -1){
			perror("fork failed\n");
			exit(1);
		}
	}
	char* argv1[] = {"ls", "ls", "-l", NULL};
	char* argv2[] = {"ps", "aux", NULL};
	if(i == 0){
		//execv("ls", "ls", "-l", NULL);
		execv(argv1[0], argv1);
	}else if(i == 1){
		//execv("ps", "aux", NULL);
		execv(argv2[0], argv2);
	}else{
		for(int i= 0; i < 2; i++){
			wait(NULL);
		}
	}*/
}
int main(){
	//test01();
	test02();
	return 0;
}
