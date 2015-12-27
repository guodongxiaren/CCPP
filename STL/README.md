STL
===
Standard Template Library
-------------------------
##内容
|概念|描述|
|:--:|----|
|[容器](./Container.md)|类模板|
|[迭代器](./Iterator.md)|类似指针|
|[算法](./Alogrithm.md)|函数模板|

#Tip
##resize、reserve
- resize重新调整容器大小，即size()返回值会变化，如果是增大容量，则用元素的默认构造函数去构造元素。
- reserve是预留容器的大小，即size()返回值不变。避免在增加元素时，频繁进行容器大小的调整操作。