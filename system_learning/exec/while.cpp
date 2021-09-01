#include <iostream>
#include <unistd.h>
int main() {
	int i = 10;
	while(i--){
		// sleep(1);
		std::cout << i << " ";
	}
	return 0;
}
