STL 5大组件

1.容器(containers)：
容器是容纳、包含一组元素或元素集合的对象
其中基本容器：向量（vector）、双端队列（deque）、链表（list）、集合（set）、多重集合（multiset）、映射（map）、多重映射（multimap）

2.迭代器（iterators）
用来在一个对象群集的元素上进行遍历，位所有容器提供了一组很小的公共接口。
迭代器类型：输入迭代器（读取）、输出迭代器（写入）、前向迭代器(单项遍历)、双向迭代器（双向遍历）、随机访问迭代器

3.算法（Algorithms）
用于处理群集内的元素，与迭代器协助，进行搜寻、排序、修改等操作。

4.适配器
接口类，为已有的类提供新的接口，简化、约束、隐藏或者改变类提供的服务集合。
分为
容器适配器：用来扩展7中基本容器，利用基本容器扩展形成栈
迭代器适配器（反向迭代器、插入迭代器、IO流迭代器）
函数适配器：函数适配器

5.内存分配器
