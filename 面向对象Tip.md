面向对象Tip&Trick
=========
##类的成员可以是自己吗？
```cpp
class base{
private:
	base b;
};
```
编译时会出错。只能写成指针的形式。
```cpp
class base{
private:
	base *b;
};
```
`base b`在编译期必须先定义好base类，然而base正在定义的过程之中，显然base是未定义的。但是指针的话，编译器就会丢给运行时去识别。
>C中的struct在定义的时候也是同理，只能出现指针的形式。

##多态分类
- 通用多态
  - 参数多态 （模板参数）
  - 包含多态 （虚函数覆盖）
- 特定多态
  - 重载多态
  - 强制多态 （强制类型转换）
  
另外从实现角度来看分为：
- 编译时多态 （模板、重载）
- 运行时多态 （虚函数）

##各种对象构造方式
```cpp
class Foo
{
public:
	Foo();
	Foo(int);
};
...
// main中
Foo a = Foo(); 		// 正确
Foo a = Foo;		// 错误
Foo b = new Foo();	// 正确
Foo b = new Foo;	// 正确

Foo a();			// 错误
Foo a(100);			// 错误

Foo();				// 正确，构造了匿名对象
```
##const成员函数重载问题
一个成员函数被标记为const，表示其不能修改类的成员。但是这个函数与无const版本是合法重载。
```cpp
class A{
private:
    int a;
public:
    A(int aa):a(aa){}
    // 以下两个重载均合法
    void echo(int b){cout<<b<<endl;}
    void echo(int b)const{cout<<a<<endl;}
};
```
此时这两个成员函数到底哪个被调用取决于类的常量性。
```cpp
int main()
{
	A a0(1);
	a0.echo(2);   // 输出1
	const A a1(1);
	a1.echo(2);   // 输出2
}

```
##纯虚析构函数一定要被实现
- 纯虚析构函数一定要被实现，即使重新实现子类的析构函数。那么也一定会沿着倒序的继承链来依次调用析构函数。
- 普通的纯虚析构函数，OK，你可以去实现它，但它决不会会被调用，因为是抽象类不会被实例化，子类则一定会重新实现纯虚函数。
- 只有纯虚析构函数的类（虽然这个函数被实现了）也是抽象类，不能被实例化。


