#include <iostream>
#include <unistd.h>
#include <pthread.h>

struct game{
	int num;
	struct game * next;
}; // 产品结构体
struct game * head = NULL;
struct game * tmp = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 定义并初始化互斥锁和条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void* argv){
	while(1){
		tmp = new game;
		tmp->num = rand()%1000+1;
		std::cout << "---producer----" << tmp->num << std::endl;
		// 访问共享数据前加锁，访问完之后立即解锁
		pthread_mutex_lock(&mutex);
		tmp->next = head;
		head = tmp;
		pthread_mutex_unlock(&mutex);
		
		pthread_cond_signal(&cond);
		sleep(rand()%3);
	}
	return NULL;
}
void* consumer(void* argv){
	while(1){
		pthread_mutex_lock(&mutex);
		while(head == NULL){
			pthread_cond_wait(&cond, &mutex);
		}
		tmp = head;
		head = tmp->next;
		pthread_mutex_unlock(&mutex);
		std::cout << "---consumer---" << tmp->num << std::endl;
		delete tmp;
		tmp = NULL;
		sleep(rand()%3);
	}
	return NULL;
}


int main() {
	pthread_t ptid, ctid;// 创建消费和生产线程
	int ret = pthread_create(&ptid, NULL, producer, NULL);
	if(ret != 0){
		std::cout << strerror(ret) << std::endl;
	       	exit(1); 
	} 
	ret = pthread_create(&ctid, NULL, consumer, NULL);
       	if(ret != 0){ 
		std::cout << strerror(ret) << std::endl;
	       	exit(1);
	}

	pthread_join(ptid, NULL);
	pthread_join(ctid, NULL);

	return 0;
}
