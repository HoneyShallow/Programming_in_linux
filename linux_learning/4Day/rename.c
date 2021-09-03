#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	if(argc < 3){	
		printf("a.out oldname newname\n");
		exit(1);
	}
	int ret = rename(argv[1], argv[2]);
	if(ret == -1) {
		perror("rename");
		exit(1);
	}
	return 0;
}
