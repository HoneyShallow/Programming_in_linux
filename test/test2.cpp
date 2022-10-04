#include <iostream>
#include <array>
#include <algorithm>

template<typename T>
void outint(const int &);

template<typename T>
void outint(const int &x){
	std::cout << x << "";
}
int main() {
	std::array<int, 0> a;
	std::cout << "a.size = " << a.size()
		<< " a.max_size = " << a.max_size()
		<< std::endl;
	std::cout << "a：";
	std::for_each(a.begin(), a.end(), outint<int>);
	return 0;
}
