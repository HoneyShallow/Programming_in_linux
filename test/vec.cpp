#include <iostream>
#include <vector>
#include <algorithm>
int main(){
	using namespace std;
	vector<vector<int>> seen(3, vector<int>(1<<3));
	auto print = [](int &x){
		cout << x << " ";
	};
	for(auto & see:seen){
		for_each(see.begin(), see.end(), print);
		cout << endl;
	}
	return 0;
}
