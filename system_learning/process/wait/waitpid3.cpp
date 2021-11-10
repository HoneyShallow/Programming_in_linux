#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
/*
< -1   回收与|pid|同组的所有进程
-1     回收所有子进程
0      回收和当前调用进程同组的所有进程
> 0    回收pid所指定的进程

*/
int main(int argc, char *argv[])
{
	int n = 5;				
	if(argc == 2){	
		n = atoi(argv[1]);
	}
	int i;
	for(i = 0; i < n; i++)	 {
        pid_t p = fork();
		if(p == 0) {
			break;			
        } 
    }

	if(n == i){  // parent
		sleep(n);
		printf("I am parent, pid = %d\n", getpid());
        for (int i = 0; i < n; i++) {
            pid_t tmp = waitpid(0, NULL, WNOHANG);
            printf("wait  pid = %d\n", tmp);
        }
	} else {
		sleep(i);
		printf("I'm %dth child, pid = %d\n", 
				i+1, getpid());
	}

	return 0;
}
