#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	struct stat st;
	int ret = lstat("s.s", &st);
	if(ret == -1) {
		perror("stat error");
		exit(1);
	}
	printf("file size = %lld\n", (long long)st.st_size);
	if((st.st_mode & S_IFMT) == S_IFREG) {
		printf("该文件是普通文件\n");
	}

	if(st.st_mode & S_IRUSR) {	
		printf("r");
	}
	else {
		printf("-");
	}

	if(st.st_mode & S_IWUSR) {	
		printf("w");
	}
	else {
		printf("-");
	}

	if(st.st_mode & S_IXUSR) {	
		printf("x");
	}
	else{	
		printf("-");	
	}
	printf("\n");
	return 0;
}
