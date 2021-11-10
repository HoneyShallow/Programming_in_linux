#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

int main()
{
	int flg = 0;
	pid_t pid = fork();
	pid_t pid2 = fork();
	
	pid_t wpid;
	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
		sleep(5);				
		exit(4);
	} else {					//parent
		do {
			pid_t wpid = waitpid(pid, NULL, WNOHANG);
			printf("---wpid = %d--------%d\n", wpid, flg++);
			if(wpid == 0){
				printf("NO child exited\n");
				sleep(1);		
			}
		} while (wpid == 0);		//子进程不可回收

		if(wpid == pid){		//回收了指定子进程
			printf("I'm parent, I catched child process,"
					"pid = %d\n", wpid);
		} else {
			printf("other...\n");
		}
	}

	return 0;
}
