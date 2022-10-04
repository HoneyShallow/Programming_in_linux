#include <iostream>
#include <time.h>
int main() {
	time_t cur = time(NULL);
	std::cout << cur << std::endl;
	return 0;
}
