#include <iostream>
#include <cstring>
using namespace std;

struct person{
	double m_salary;
	char * m_name;
};

class manager {
private:
	person * worker_info; // 保存员工信息的数组
	int max_num; // 最多保存的员工信息量
	int cur_num; // 当前已经保存的员工数量
public:
	manager(){} // 默认构造函数
	manager(int num = 0):max_num(num){
		cur_num = 0;
		worker_info = new person[max_num];
	} // 有参构造函数
	// 拷贝构造函数和赋值运算符重载都采用了深拷贝，是为了防止浅拷贝的纯值拷贝带来的问题，多次析构同一对象
	manager(const manager& man_old) {
		this->max_num = man_old.max_num;
		this->cur_num = man_old.cur_num;
		// 由于该类使用了指针的成员变量，所以拷贝函数必须采用深拷贝
		this->worker_info = new person[this->max_num];
		for(int i = 0;i < this->cur_num; i++){
			this->worker_info[i] = man_old.worker_info[i];
		}
	}
	// 利用[]运算符重载录入成员信息
	double& operator[](const char * name){
		person * p = nullptr;
		// 首先遍历worker_info，如果该员工存在，返回其薪水
		for(p = worker_info; p != worker_info + this->cur_num; p++){
			if(strcmp(p->m_name, name) == 0)return p->m_salary;
		}
		// 如果该员工信息不存在，将该员工信息录入worker_info
		// 如果发生下边这种情况，理应直接报错中断程序，下边只是打印了错误信息
		if(this->cur_num == this->max_num)
			cout << "可存储空间不足!" << endl;
		p->m_name = new char[strlen(name)+1];
		strcpy(p->m_name, name);
		this->cur_num++;
		p->m_salary = 0;
		return p->m_salary;

	}
	manager& operator=(const manager & old) {
		if(this == &old) return *this;
		if(this->worker_info != nullptr) delete [] worker_info;
		// worker_info是数组对象指针，所以需要使用delete[];
		worker_info = new person[old.max_num];
		this->max_num = old.max_num;
		this->cur_num = old.cur_num;
		for(int i = 0; i < this->cur_num; i++){
			this->worker_info[i] = old.worker_info[i];
		}
	}
	~manager(){
		if(this->worker_info != nullptr) delete [] worker_info;
	}

	void print() {
		for(int i = 0; i < this->cur_num; i++){\
			cout << worker_info[i].m_name << " "
			     << worker_info[i].m_salary << endl;
		}
	}
};
int main() {
	manager m(3);
	m["张三"] = 2188.88;
	m["李斯"] = 1230.07;
	m["王无"] = 3200.97;
	cout << "张三\t" << m["张三"] << endl;
	cout << "李斯\t" << m["李斯"] << endl;
	cout << "王无\t" << m["王无"] << endl;
	cout << "---------------整体输出------------\n";
	m.print();
	// 经验证，拷贝构造函数和赋值运算符重载均正常
	manager m1(m);//
	m1.print();
	manager m2 = m1;
	m2.print();
	return 0;

}
