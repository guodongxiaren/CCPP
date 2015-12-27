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