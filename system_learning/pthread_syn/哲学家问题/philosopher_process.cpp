#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void)
{
	// mmap返回值为泛型指针
	sem_t *s = (sem_t*)mmap(NULL, sizeof(sem_t)*5, PROT_READ|PROT_WRITE, 
			MAP_SHARED|MAP_ANON, -1, 0);
	// 借助匿名映射而不需要借助文件完成映射
	if (s == MAP_FAILED) {
		perror("fail to mmap");
		exit(1);
	}
	for (int i = 0; i < 5; i++)// 创建5个用于进程间同步的信号量
		sem_init(&s[i], 0, 1);  //信号量初值制定为1，信号量，变成了互斥锁
	int i;
	for (i = 0; i < 5; i++){
		pid_t pid = fork();
		if (pid == 0){
			break;
		}
		else if(pid == -1) {
			perror("fork error");
			exit(1);
		}
	}
	if (i < 5) {				//子进程
		int l, r;
		srand(time(NULL));

		if (i == 4) 
			l = 0, r = 4;
		else
			l = i, r = i+1;
		while (1) {
			sem_wait(&s[l]);
			if (sem_trywait(&s[r]) == 0) {
				std::cout << char ('A' +i) << "is eating\n";
				sem_post(&s[r]);
			}
			sem_post(&s[l]);
			sleep(rand() % 5);
		}
		exit(0);
	} 

	for (i = 0; i < 5; i++)
		wait(NULL);	

	for (i = 0; i < 5; i++)
		sem_destroy(&s[i]);

	munmap(s, sizeof(sem_t)*5);

	return 0;
}

