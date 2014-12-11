函数模板
==========
##基本形式
```cpp
template <typename T>
T& max(const T &a , const T &b)
{
    if(a < b)
	    return b;
	else
	    return a;
}
```
这样这个函数就能比较任意类型的两个变量的大小了。template那一行也可以与函数声明写在一行。    
>在C中，由于没有模板的概念，要实现该功能一般使用**宏定义**来实现，比如：  
`#define max(a,b) ((a) > (b) ? (a) : (b))`    
但是有时候宏定义却不能得出如你所愿的结果。比如在变量a发生了自增操作的时候。

##inline函数模板
模板函数也可以与非模板函数一样声明为[inline](#inline)。注意关键字inline要放置在模板参数之后。
```cpp
template <typename T>
inline T& max(const T &a , const T &b)
{
    if(a < b)
	    return b;
	else
	    return a;
}
```
###inline
在C++中,inline不仅可以用来类的成员函数上，还可以用在普通的函数上。这样的目的是替换C语言中*函数式宏定义*。  
比如前面的`#define max(a,b) ((a) > (b) ? (a) : (b))` 。宏定义在编译期，对相应的符号进行替换，提高了程序运行期的效率。  
而inline正是为了取代这一宏定义而产生的。inline函数在编译期直接展开，而一般函数则是在运行时进行调用，需要去跳转到函数定义时的位置。  
所以inline提高了程序运行效率，却增加了程序的大小（如果函数多次调用就会展开多次，故而增加了代码的长度）。