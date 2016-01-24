算法
====
STL的算法库的设计思想不符合面向对象的风格，但是符合泛型编程的风格。
>面向对象主张将操作和数据封装到一起，但是STL并没有为每一种容器实现每一种算法，而是设计了能够操作各种类型容器的算法库。

##查找类算法
|函数名|描述
|------|----
|*min_element*|找出最小值
|*max_element*|找出最大值
|find|寻找某一值

以上函数的迭代器可以是常量迭代器
##顺序类算法
|函数名|描述
|------|----
|sort|排序（缺省为升序）
|reverse|逆序排列
因为涉及元素的变动，所以以上函数的迭代器不能是常量迭代器

##排序类算法
|函数名|描述
|------|------
|partition|将所有满足条件的元素移到前部，返回第一个不满足条件的迭代器。
|stable_partition|同上，不过是稳定的
|nth_element|将满足条件的前n个元素移到前部，该部分无序
|partial_sort|部分排序，排序部分有序
|sort|快排，比qsort效率高
|stable_sort|稳定快排，比sort效率低

>sort、stable_sort、partial_sort和nth_element算法要求随机访问迭代器，即适用于vector、string、deque和数组。对关联容器中元素排序无意义。list是唯一有排序需求却无法使用这些排序算法的容器，为此，list有成员函数sort（稳定排序）。
>>partition和stable_partition只要求双向迭代器，所以适用于所有标准序列容器。
>>>————《Effective STL》
