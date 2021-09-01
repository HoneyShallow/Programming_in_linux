#include <iostream>
#include <cstdlib>
#include <cstring>
int my_atoi(const char * str){
	int ret = 0;
	while(*str){
		while(isspace(*str)){// 如果字符是空白符，跳过
			str++;
		}
		if(!isdigit(*str)) break;
		// 也即是说如果首个非空格的字符不是数字，那么返回值为0
		while(isdigit(*str)){
			ret = ret*10 + *str-'0';
			str++;
		}
		if(ret) break;
		//如果已经知道首个最长字符串个构成的数字，跳出循环，返回该数字
		/*
		if(!isdigit(*str++))
			continue;
		*/
	}
	return ret;
}
int main() {
	using std::cout;
	using std::endl;
//	const char * str = "word with 2 ";
	char str[50];
	cout << "enter a string: ";
	std::cin.getline(str, 50);
	cout << "atoi(str):" << atoi(str) << endl;
	cout << "my_atoi(str):" << my_atoi(str) << endl;
	return 0;
}
