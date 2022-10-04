#include <iostream>
#include <unistd.h>

int main(){
	alarm(1);
	for(int i = 0;;i++){
		std::cout << i << std::endl;
	}
	return 0;
}
