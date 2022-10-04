#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include <string>

template<typename T>
void outint(const T & x){
	cout << x << " ";
}
int main() {
	int arr[] = {99, 10, 1, 6, 8, 9, 5, 10};
	vector<int> v(arr, arr + 8);
	sort(v.begin(), v.end(), std::less<int>());
 	for_each(v.begin(), v.end(), outint<int>);
//	auto index = upper_bound(v.begin(), v.end(), 0);
// 	vector 没有成员变量upper_bound(), 所以这里只能采用公共算法函数
//	if(index != v.begin())	cout << *(index-1) << endl;
//	else cout << "未找到" << endl;
//	cout << string({127}) << endl;
	return 0;
}
