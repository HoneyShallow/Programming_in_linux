#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>
#include <ctime>
int main() {
    using namespace std;
    clock_t timeStart = clock();
    stack<int, list<int>> c;
    for (long i = 0; i < 100000; i++)
        c.push(i+1);
    cout << "stack.size()= " << c.size() << endl;
    cout << "stack.top()= " << c.top() << endl;
    c.pop();
    cout << "stack.size()= " << c.size() << endl;
    cout << "stack.top()= " << c.top() << endl;
    cout << "use stack milli-seconds : " << (double)(clock() - timeStart)/CLOCKS_PER_SEC << endl;
    timeStart=clock();
    stack<int, deque<int>> c1;
    for (long i = 0; i < 100000; i++)
        c1.push(i+1);
    cout << "stack.size()= " << c1.size() << endl;
    cout << "stack.top()= " << c1.top() << endl;
    c1.pop();
    cout << "stack.size()= " << c1.size() << endl;
    cout << "stack.top()= " << c1.top() << endl;
    cout << "use stack milli-seconds : " << (double)(clock() - timeStart)/CLOCKS_PER_SEC << endl;
    // vector可以作为stack的底层容器
    stack<int, vector<int>> c2;
    for (long i = 0; i < 100000; i++)
        c2.push(i+1);
    cout << "stack.size()= " << c2.size() << endl;
    cout << "stack.top()= " << c2.top() << endl;
    c2.pop();
    cout << "stack.size()= " << c2.size() << endl;
    cout << "stack.top()= " << c2.top() << endl;
    cout << "use stack milli-seconds : " << (double)(clock() - timeStart)/CLOCKS_PER_SEC << endl;
    return 0;
}

