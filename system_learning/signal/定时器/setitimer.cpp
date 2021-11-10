#include <iostream>
#include <sys/time.h>
/*
 * struct itimerval  {
        struct timeval{
            tv_sec;
            tv_usec;
        } it_interval; // 表示下一个记时器的值

        struct timeval {
            tv_sec;
            tv_usec;
        } it_value; // 表示当前记时器的值

    } it, oldit;
*/
unsigned int my_alarm(unsigned int sec)
{
	struct itimerval it, oldit;

	it.it_value.tv_sec = sec;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 0;

    	int ret = setitimer(ITIMER_REAL, &it, &oldit);
   	if (ret == -1) {
	        perror("setitimer");
        	exit(1);
    	}
	return oldit.it_value.tv_sec;
}

int main(void)
{
	int i;
	my_alarm(1);  //alarm(sec);

	for(i = 0; ; i++)
		printf("%d\n", i);

	return 0;
}
