#include <iostream>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m[5]; //5个哲学家定义五把锁

void *tfn(void *arg)
{
	long l, r;
	srand(time(NULL));
	long i = (long)arg;
	// 默认情况下，i哲学家左手拿i号锁，右手拿i+1号锁即可完成就餐
	if (i == 4)//最后一位哲学家则顺序相反
		l = 0, r = i;
	else
		l = i; r = i+1;

	while (1) {
		pthread_mutex_lock(&m[l]);
		if (pthread_mutex_trylock(&m[r]) == 0) {
			// 不同于lock，trylock在拿不到锁时，会直接返回
			// 而不阻塞
		       	//尝试去拿右手边的锁，如果成功，可以就餐了
			//如果拿不到，放弃已有的锁
			std::cout << char('A'+i) << "is eating\n";
			pthread_mutex_unlock(&m[r]);
		}
		pthread_mutex_unlock(&m[l]);
		sleep(rand() % 5);// 留出时间等待其他人操作
	}

	return NULL;
}

int main(void)
{
	pthread_t tid[5];
	
	// 创建5把锁
	for (int i = 0; i < 5; i++)
		pthread_mutex_init(&m[i], NULL);
	// 创建5个线程代表5个哲学家
	for (long i = 0; i < 5; i++)
		pthread_create(&tid[i], NULL, tfn, (void *)i);
	// 等待回收子线程
	for (int i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
	// 销毁5把锁
	for (int i = 0; i < 5; i++)
		pthread_mutex_destroy(&m[i]);

	return 0;
}

