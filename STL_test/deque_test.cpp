#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	using namespace std;
	vector<int> v1{1, 2,3,45,9};
	// std::size_t len = distance(v1.begin(), v1.end());	
	auto outint = [](const int & x){cout << x << " ";};
	for_each(v1.begin(), v1.end(), outint);
	cout << endl;

	v1.push_back(v1.back());
	auto back1 = v1.end();
	--back1;
	auto back2 = back1;
	--back2;
	auto pos = v1.begin() + std::ptrdiff_t(3);
	copy_backward(pos, back2, back1);
	*pos = 66;
	for_each(v1.begin(), v1.end(), outint);
	return 0;
}
