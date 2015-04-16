/**
template<
    class T,
    class Allocator = std::allocator<T>
> class deque;
std::deque（双端队列）是一个索引序列的容器，允许快速的插入和删除的开始和结束。


效率：
随机访问 - 常数O(1)
在结尾或开头插入或移除元素 - 摊销不变O(1)
插入或移除元素 - 线性O(n)
*/

