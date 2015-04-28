/**
移除性算法：
remove、remove_if，满足特定条件的范围内[first, last)中移除所有元素。

变序性算法：
rotate、rotate_copy，将区间内的元素旋转、复制

排序算法：
sort

已序区间算法：
lower_bound、upper_bound，返回指向第一个不小于/大于给定值的元素的迭代器 

数值算法：
accumulate，计算区间内元素的和 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void printf_elemnt(int n) {
    cout << n << ' ';
}

bool my_compare(int a, int b) {
    return a > b;
}

int multiply(int x, int y)
{
    return x*y;
}

int main(void) {
    int a[] = {1, 2, 2, 3, 4, 5, 6};
    vector<int> v(a, a + 7);
    
    //remove
    vector<int>::iterator it = remove(v.begin(), v.end(), 2);
    v.erase(it, v.end());
    for_each(v.begin(), v.end(), printf_elemnt);    //1 3 4 5 6
    cout << endl;
    
    //rotate
    rotate(v.begin(), v.begin() + 2, v.end() - 1);  //4 5 1 3 6
    for_each(v.begin(), v.end(), printf_elemnt);
    cout << endl;
    
    //sort
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), printf_elemnt);    //1 3 4 5 6
    cout << endl;
    
    sort(v.begin(), v.end(), my_compare);
    for_each(v.begin(), v.end(), printf_elemnt);    //6 5 4 3 1
    cout << endl;
    
    //lower_bound, 有序（默认从小到大）
    int b[] = {1, 10, 10, 14, 15, 16};
    vector<int> v2(b, b + 6);
    auto lower = lower_bound(v2.begin(), v2.end(), 10); //>= 10
    auto upper = upper_bound(v2.begin(), v2.end(), 10); //>  10
    cout << "lower_bound : " << lower - v2.begin() << endl; //1
    cout << "upper_bound : " << upper - v2.begin() << endl; //3
    
    //aucumulate
    auto sum = accumulate(v2.begin(), v2.end(), 0);
    cout << " sum : " << sum << endl;
    
    auto sum2 = accumulate(v2.begin(), v2.end(), 1, multiply);
    cout << " sum2 : " << sum2 << endl;
    
    return 0;
}