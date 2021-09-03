#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

// 定义函数，读取指定目录文件的个数
int get_file(const char * root) {
	DIR* dir = NULL;
	dir = opendir(root);
	if(dir == NULL) {
		perror("opendir error");
		exit(1);
	}
	int total = 0;
	char path[1024] = {0};
	// 循环读目录中的文件
	 struct dirent* ptr = NULL;
	while((ptr = readdir(dir)) != NULL) {
		// 不处理.和..目录，隐藏文件
		if(strcmp(ptr->d_name, ".") ==  0 || strcmp(ptr->d_name, "..") == 0) {
			continue;
		}
		// 判断是不是文件
		if(ptr->d_type == DT_REG) {
			total++;
		}
		// 如果是目录，递归读取
		if(ptr->d_type == DT_DIR) {
			sprintf(path, "%s/%s", root, ptr->d_name);
			// 将该目录的路径写入到path中
			total += get_file(path);
		}

	}
	closedir(dir);
	return total;
}

int main(int argc, char * argv[]) {
	if(argc < 2) {
		printf("a.out dir\n");
		exit(1);
	}
	// 读目录，统计文件个数
	int total = get_file(argv[1]);
	printf("%s has file number: %d \n", argv[1], total);
	return 0;
}
