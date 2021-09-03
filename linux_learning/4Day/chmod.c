#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[]) {
	if(argc < 3) {	
		printf("a.out filename mode\n");
		exit(1);
	}
	int mode = strtol(argv[2], NULL, 8);
	int ret = chmod(argv[1], mode);
	if(ret == -1) {
		perror("chmod");
		exit(1);
	}
	return 0;
}
