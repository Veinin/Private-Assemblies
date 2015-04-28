/**
变动性、会修改序列内容的操作算法

for_each改变元素
取决于第三个参数，所传入的函数

copy、copy_if
复制中的元素定义的范围内，由[first, last)到另一个范围开始于d_first。

copy_n
复制一定数目的元素到新的位置 

copy_backward
按从后往前的顺序复制一个范围内的元素

transform
将一个函数应用于某一范围的元素，原范围元素不改变，只改变目标范围元素

replace
将所有满足特定条件的元素替换为另一个值 

repalce_copy
复制一个范围内的元素，并将满足特定条件的元素替换为另一个值

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

bool check_7(int n) {
    return n > 7;
}

int add_2(int n) {
    return n + 2;
}

int main(void) {
    vector<int> v;
    v.push_back(4);
    v.push_back(5);
    v.push_back(3);
    
    list<int> l(5);
    list<int> l2(10);
    list<int> l3(10);
    list<int> l4(10);
    
    string in = "123456789";
    string out;
    
    //for_each changed
    for_each(v.begin(), v.end(), add_3);
    for_each(v.begin(), v.end(), print_element);    //7 8 6
    cout << endl;
    
    //copy
    copy(v.begin(), v.end(), l.begin());
    for_each(l.begin(), l.end(), print_element);    //7 8 6 0 0
    cout << endl;
    
    //copy_if
    copy_if(v.begin(), v.end(), l2.begin(), check_7);
    for_each(l2.begin(), l2.end(), print_element);  //8 0 0 0 0 0 0 0 0 0
    cout << endl;
    
    //copy_n
    copy_n(in.begin(), 4, back_inserter(out));      //1234
    cout << out << endl;
    
    //copy_backward
    copy_backward(v.begin(), v.end(), l2.end());
    for_each(l2.begin(), l2.end(), print_element);  //8 0 0 0 0 0 0 7 8 6
    cout << endl;
    
    //transform
    transform(l2.begin(), l2.end(), l3.begin(), add_2);
    for_each(l3.begin(), l3.end(), print_element);  //10 2 2 2 2 2 2 9 10 8
    cout << endl;
    
    //replace
    replace(l3.begin(), l3.end(), 2, 0);
    for_each(l3.begin(), l3.end(), print_element);  //10 0 0 0 0 0 0 9 10 8
    cout << endl;
    
    //replace_copy
    replace_copy(l3.begin(), l3.end(), l4.begin(), 0, 1);
    for_each(l4.begin(), l4.end(), print_element);  //10 1 1 1 1 1 1 9 10 8
    cout << endl;
    
    return 0;
}