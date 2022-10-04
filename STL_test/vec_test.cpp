#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <typeinfo>

void print(const vector<int> & vec){
	for(auto x:vec)
		cout << x << " ";
	cout << endl;
}
void test() {
	vector<int> vec(3, 100);
	print(vec);

	auto it = vec.begin();
	it = vec.insert(it, 200);
	print(vec);
	cout << "*it: "  << *it << endl;

	vec.insert(it, 2, 300);
	print(vec);
}
int main() {
	test();
/*	vector<int> v1{7,9,10,1,2,3};
	auto outint = [](const int &x){cout << x << " ";};
	for_each(vec.begin(), vec.end(), outint);
	vector<int> v2;
	v2.assign(10, 6);
	for_each(v2.begin(),v2.end(), outint);
	cout << endl;
	v2.assign(v1.begin(), v1.end());
	for_each(v2.begin(), v2.end(), outint);
	auto it = v1.data();
	cout << *it << endl;
	cout << typeid(v1.data()).name() << endl;*/
	return 0;
}
