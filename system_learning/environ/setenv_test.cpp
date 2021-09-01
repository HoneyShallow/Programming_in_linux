#include <iostream>
#include <cstdlib>

int main(){
	using namespace std;
	const char* name = "ABO";
	char * val;
	val = getenv(name);
	cout << "1." << name << " = " << val << endl;

	setenv(name, "haha-day-and-night", 1);

	val = getenv(name);
	cout << "1." << name << " = " << val << endl;

	int ret = unsetenv("ABO");
	// 如果在这里删除一个不存在的环境变量，返回值依旧为0，也即删除成功，只有出现"ABO="类似的参数时，才会返回-1
	cout << "ret = " << ret << endl;

	val = getenv(name);
	cout << "1." << name << " = " << val << endl;
	return 0;
}
