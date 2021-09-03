#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[]) {
	if(argc < 3) {	
		printf("a.out filename mode\n");
	}
	int ret = chown(argv[1], 0, 0);
	if(ret == -1) {
		perror("chown");
		exit(1);
	return 0;
}
