#include <iostream>
#include <unordered_map>
using namespace std;
#include <string>

int main() {
	unordered_map<std::string,int> hash;
	hash["dai"] = 100;
	cout << hash["cong"] << endl;
	return 0;
}
