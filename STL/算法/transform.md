transform
==========
>http://www.cplusplus.com/reference/algorithm/transform/

将一个容器中某一段元素进行某种操作（一元/二元）后再插入新的容器中。
##函数原型
两个重载
```cpp
// 一元
template <class InputIterator, class OutputIterator, class UnaryOperation>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperation op);
```

```cpp
// 二元
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class BinaryOperation>
  OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op)
```
多了一个参数`first2`，表示二元的操作的第二个参数。
##源码
```cpp
template <class InputIterator, class OutputIterator, class UnaryOperator>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperator op)
{
  while (first1 != last1) {
    *result = op(*first1);  // or: *result=binary_op(*first1,*first2++);
    ++result; ++first1;
  }
  return result;
}
```
