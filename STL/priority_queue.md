priority_queue
=====
优先队列
-----
优先队列默认是数值越大，优先级越高，也就是降序排列。
##头文件
```cpp
#include <queue>
```
##重载优先级
```cpp
    priority_queue<int, vector<int>, greater<int> > q;
```
使之升序排列。
>注意最后的`> >`之间必须有空格(C++11之后，可以取消这个空格了)。

##注意
优先队列的元素类型不能是引用，否则会报错，可以是指针。
##自定义类的优先级
```cpp
// 使用struct简化描述
struct node
{
    int weight;
    node *left;
    node *right;	
};
```
需要重载比较操作符，可以以友元，成员函数，或全局函数的方式来重载。
默认使用的是`less<>`（*降序*），所以默认重载`<`，如果你声明的时候传递了参数`greater<>`（*升序*），则要重载`>`。
```cpp
bool operator< (node &a, node &b)
{
    return a.weight < b.weight;
};
```
当优先队列里的元素类型是指针的时候，重载操作符的方法，已不可用。因为**关系比较操作符**重载是针对**类类型**和**枚举类型**，
指针类型，不会得到匹配。所以要采用其他的方式。（至少有一个参数是类类型或枚举）
```cpp
struct cmpNode
{
    bool operator() (node *a, node *b) //重载()，必须作为类的成员函数，不能是全局函数
	{
	    return a->weight > b->weight;  //排序结果为升序
		//return a->weight < b->weight;  //排序结果为降序
	}
};
```
声明的时候：
```
priority<node *, vector<node *>, cmpNode> nodes;
```

----------------------------------------------------------------------
##类模板
`std::priority_queue`
```cpp
template <class T, class Container = vector<T>,
  class Compare = less<typename Container::value_type> > class priority_queue;
```
##成员 
|成员名|描述|
|:----------:|--------------|
|*value_type*|第一个参数T|
|*container_type*|第二个参数Container|
|*sieze_type*|通常和*size_t*相同|

##成员函数
|函数名|返回值|
|:----:|:----:|
|(constructor)||
|empty|bool|
|pop|void|
|push|void|
|size|*size_type*|
|top|_const value_type&_|
>优先队列没有front成员函数，取而代之是top函数。queue有front成员函数。
因为优先队列是堆实现的，想象一下堆的结构，就知道top这个词更合理。

