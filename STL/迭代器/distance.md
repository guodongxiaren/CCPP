distance()函数
========
##头文件
`<iterator>`
##描述
求两个迭代器直接的距离，顺序不能反。  
>计头不计尾

##例子
```cpp
vector<int> nums;
...
distance(nums.begin(), nums.end()); // 与nums.size()相同。
```