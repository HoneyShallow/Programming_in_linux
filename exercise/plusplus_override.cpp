#include <iostream>
#include <cmath>
using namespace std;

class Clock {
private:
	int c_hour;
	int c_minute;
	int c_second;
public:
	Clock(int hour = 0, int minute = 0,int second = 0);
	void show_time() const;
	Clock& operator ++(); // 前缀++
	Clock operator ++(int); // 后缀++
	~Clock(){}
};

Clock::Clock(int hour, int minute, int second){
	if(hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60){
		this->c_hour = hour;
		this->c_minute = minute;
		this->c_second = second;
	} else {
		cout << "该时间格式有误!" << endl;
	}
}
Clock& Clock::operator ++() {
	c_second++;
	if(c_second >= 60){
		c_minute++;
		c_second -= 60;
		if(c_minute >= 60){
			c_hour++;
			c_minute -= 60;
			c_hour %= 24;
		}
	}
	return *this;
}
Clock Clock::operator ++(int){
	Clock tmp = *this;
	++(*this);
	return tmp;
}
void Clock::show_time() const{
	cout << "current time :" << c_hour << "-"
		<< c_minute << "-" << c_second << endl;
}
int main() {

	Clock cl(23,59,59);
	cout << "原始时间: ";
	cl.show_time();
	
	cout << "后缀++之后的时间：";
	(cl++).show_time();

	cout << "前缀++之后的时间 : ";
	(++cl).show_time();
	return 0;
}
