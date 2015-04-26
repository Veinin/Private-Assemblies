/**
非变动性、不修改序列内容的操作算法

for_each
将给定的函数f的结果运用在从[first, last)每一个迭代器所指向的内容，依照顺序。 
如果InputIt是一个可变的迭代器，f可以通过解引用迭代器来修改处于范围内的元素。
如果f返回一个结果，该结果将被忽略.

min_element
使用operator<的值进行比较的第一个版本，第二个版本使用给定的比较函数comp.

max_element
查找的范围内[first, last)中最大的元素。
使用operator<的值进行比较的第一个版本，第二个版本使用给定的比较函数comp.

find、find_if、find_if_not
这些功能[first, last)满足特定的条件的范围内找到的第一个元素
原文：
您可以帮助我们检查、纠正翻译中的错误。详情请点击这里。
find搜索元素等于value
find_if搜索元素的谓词p回报true
find_if_not搜索元素的谓词q回报false

search
搜索范围内的第一个序列的元素。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printfVal(int value) {
    cout << value << ' ';
}

bool greater_than_3(int n) {
    return n > 3;
}

int main(void) {
    vector<int> v;
    
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
    
    //for_each
    for_each(v.begin(), v.end(), printfVal);
    cout << endl;
    
    //min_element
    it = min_element(v.begin(), v.end());
    cout << "min element : " << *it << endl;
    
    //max_element
    it = max_element(v.begin(), v.end());
    cout << "max element : " << *it << endl;
    
    //find
    it = find(v.begin(), v.end(), 3);
    if(it != v.end())
        cout << it - v.begin() << endl;
    else
        cout << "not found!" << endl;
    
    //find_if
    it = find_if(v.begin(), v.end(), greater_than_3);
    if(it != v.end())
        cout << it - v.begin() << endl;
    else
        cout << "not found!" << endl;

    //search
    vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    it = search(v.begin(), v.end(), v2.begin(), v2.end());
    if(it != v.end())
        cout << it - v.begin() << endl;
    else
        cout << "not found!" << endl;
    
    vector<int> v3;
    v3.push_back(8);
    v3.push_back(10);
    it = search(v.begin(), v.end(), v3.begin(), v3.end(), twice);
    if(it != v.end())
        cout << it - v.begin() << endl;
    else
        cout << "not found!" << endl;
    
    return 0;
}