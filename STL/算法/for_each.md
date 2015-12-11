for_each
========
```cpp
template <class InputIterator, class Function>
Function for_each (InputIterator first, InputIterator last, Function fn);
```
样例
-----
###一般用法
```cpp
/*
 * from cplusplus.com
 */
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector

void myfunction (int i) {  // 函数:
	  std::cout << ' ' << i;
}

struct myclass {           // 函数对象:
	void operator() (int i) {std::cout << ' ' << i;}
} myobject;

int main () {
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each (myvector.begin(), myvector.end(), myfunction);
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each (myvector.begin(), myvector.end(), myobject);
    // for_each (myvector.begin(), myvector.end(), myclass());
	std::cout << '\n';

	return 0;
}
```
注意在以函数对象为参数的时候，传递的可以是一个类具象化后的函数对象，或者是该类直接加括号的形式。
###for_each处理返回值
```cpp
/*
 * 改编自《C++ STL标准库开发指南》
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(int elem)
{
    cout<<elem<<" ";
}

struct SUM
{
    long sum_D;
    SUM():sum_D(0){cout<<"fuck"<<endl;}
    void operator()(int elem)
    {
        sum_D += elem;
    }
    operator double()     //重载类型转换操作符无返回值
    {
        return static_cast<double>(sum_D);
    }


};
int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> myvector(a, a+10);
    for_each(myvector.begin(), myvector.end(), print);
    cout<<endl;

    double sum = for_each(myvector.begin(), myvector.end(), SUM());
    cout<<"The SUM: "<<sum<<endl;
    cout<<double(SUM())<<endl; //未重载类型转换操作符double()，则此句报错。
}
```
