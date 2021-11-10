#include <iostream>
using namespace std;

extern char** environ;
int main(){
	char** tmp = environ;
	while(tmp != nullptr){
		cout << *tmp << endl;
		tmp++;
	}
	return 0;
}
