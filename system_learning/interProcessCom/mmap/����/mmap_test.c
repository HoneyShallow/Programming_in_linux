#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/mman.h>

int main(void)
{
    int fd = open("./test.txt", O_RDWR);

    struct stat sbuf;
    stat("./test.txt", &sbuf);
    int len = sbuf.st_size;
    printf("len = %d\n", len);
    
    char *p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    strcpy(p, "hehehe");  
	std::cout << p << std::endl;

    munmap(p, len); // 解除映射
    close(fd);

    return 0;
}
