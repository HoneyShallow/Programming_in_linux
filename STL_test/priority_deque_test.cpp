#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
// #include <priority_queue>

int main() {
	vector<pair<int, int>> v;
	v.emplace_back(make_pair(90, 1));
	v.emplace_back(make_pair(90, 5));
	v.emplace_back(make_pair(80, 1));
	v.emplace_back(make_pair(50, 1));
	v.emplace_back(make_pair(60, 1));
	v.emplace_back(make_pair(70, 1));
	auto print = [](pair<int, int> x){
		//cout << x.first << " ";
		cout << x.second << " ";
	};
	for_each(v.begin(), v.end(), print);
	auto cmp = [](pair<int, int> x, pair<int, int> y){
		if(x.first < y.first) return false;
		else if(x.first == y.first) {
			return x.second > y.second;
		} else {
			return true;
		}
	};
	sort(v.begin(), v.end(), cmp);
	for_each(v.begin(), v.end(), print);
	return 0;
}
