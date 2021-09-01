#include <iostream>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1 ) {
        perror("fork");
        exit(1);
    } else if (pid > 0) {
        sleep(1);
	std::cout << "I'm parent pid = " << getpid() << ", parentID = " << getppid() << std::endl;
    } else if (pid == 0) {
	    std::cout << "child pid = " << getpid() << ", parentID = " << getppid() << std::endl;
	sleep(3);
	std::cout << "child pid = " << getpid() << ", parentID = " << getppid() << std::endl;
    }
    return 0;
}
