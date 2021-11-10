#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;
struct exit_t{
	int m_a;
	int m_b;
	exit_t():m_a(0), m_b(0){}
	exit_t(int a, int b):m_a(a), m_b(b){}
	exit_t(const exit_t & old){
		this->m_a = old.m_a;
		this->m_b = old.m_b;
	}
	~exit_t(){}
};

ostream& operator<<(ostream & os, const exit_t & old){
	os << "m_a = " << old.m_a
		<< ", m_b = " << old.m_b << std::endl;
	return os;
}
void *tfn(void *arg)
{
	exit_t *ret = new exit_t;
	//ret = malloc(sizeof(exit_t)); 

	//ret->a = 100;
	//ret->b = 300;

	pthread_exit((void *)ret);// 退出状态类型为void*
}

int main(void)
{
	pthread_t tid;// 线程id
	exit_t *retval;//退出状态

	pthread_create(&tid, NULL, tfn, NULL);

	/*调用pthread_join可以获取线程的退出状态*/
	pthread_join(tid, (void **)&retval);      //wait(&status);
	//printf("a = %d, b = %d \n", retval->a, retval->b);
	cout << *retval << endl;
	delete retval;

	return 0;
}

