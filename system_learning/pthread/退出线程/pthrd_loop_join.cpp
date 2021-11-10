#include <iostream>
#include <unistd.h>
#include <pthread.h>

int var = 100;

void *tfn(void *arg)
{
    long i = (long)arg;
    
    sleep(i);
    if (i == 1) {
        var = 333;
	std::cout <<  "var = " << var << std::endl;
        return (void *)var;

    } else  if (i == 3) {
        var = 777;
	std::cout << "I'm"<<  i+1  << "th pthread, pthread_id =" << pthread_self() << ",var = "<< var << std::endl;
        pthread_exit((void *)var);
    } else  {
	    std::cout << "I'm"<<  i+1  << "th pthread, pthread_id =" << pthread_self() << ",var = "<< var << std::endl;
        pthread_exit((void *)var);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid[5];
    long *ret[5];  

    for (long i = 0; i < 5; i++)
        pthread_create(&tid[i], NULL, tfn, (void *)i);

    for (long i = 0; i < 5; i++) {
        pthread_join(tid[i], (void **)&ret[i]);
       	std::cout << i+1 << "ret = " << (long)ret[i] << std::endl;
    }
        
    sleep(5);
    std::cout << "main pthread tid = " << pthread_self() <<  ",var = " << var << std::endl; 
    return 0;
}
