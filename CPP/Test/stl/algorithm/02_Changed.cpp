/**
变动性、会修改序列内容的操作算法

for_each改变元素
取决于第三个参数，所传入的函数

copy、copy_if、copy_n

*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void print_element(int n) {
    cout << n << ' ';
}

void add_3(int &n) {
    n += 3;
}

bool check_3(int n) {
    return n > 7;
}

int main(void) {
    vector<int> v;
    v.push_back(4);
    v.push_back(5);
    v.push_back(3);
    
    list<int> l(5);
    list<int> l2(3);
    
    //for_each changed
    for_each(v.begin(), v.end(), add_3);
    for_each(v.begin(), v.end(), print_element);    //7 8 6
    cout << endl;
    
    //copy
    copy(v.begin(), v.end(), l.begin());
    for_each(l.begin(), l.end(), print_element);
    cout << endl;
    
    //copy_if
    copy_if(v.begin(), v.end(), l2.begin(), check_3);
    for_each(l2.begin(), l2.end(), print_element);
    
    return 0;
}