unique
=======
线性扫描，“删除”邻接相同元素。其实它类似于remove算法，所以它实际并没有删除元素，并没有改变容器大小，只是对元素进行了重排。同时和remove算法一样，返回一个迭代器。该迭代器后面的元素通通是理论上可删除的。
>对已排序的容器进行unique()，比较有用

##函数原型
```cpp
template <class ForwardIterator>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last);
	
template <class ForwardIterator, class BinaryPredicate>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last,
                          BinaryPredicate pred);
```
第二个重载，多了一个参数——二元判别式（代替两个邻接元素是否相等的判断）