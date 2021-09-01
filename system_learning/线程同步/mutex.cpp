#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;      //定义锁

void *tfn(void *arg)
{
    srand(time(NULL));
    while (1) {
        pthread_mutex_lock(&mutex);

        printf("hello ");
        sleep(rand() % 3);	/*模拟长时间操作共享资源，导致cpu易主，产生与时间有关的错误*/
        printf("world\n");

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

int main(void)
{
    int flg = 5;
    pthread_t tid;
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);  // mutex==1//初始化mutex
	
	// 创建一个线程
    pthread_create(&tid, NULL, tfn, NULL);
    while (flg--) {
        pthread_mutex_lock(&mutex); // 加锁

        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
		
        pthread_mutex_unlock(&mutex); // 解锁

        sleep(rand() % 3);
    }
    pthread_cancel(tid); // kill线程
    pthread_join(tid, NULL); //回收线程

    pthread_mutex_destroy(&mutex);  //销毁锁

    return 0;
}


/*线程之间共享资源stdout*/
