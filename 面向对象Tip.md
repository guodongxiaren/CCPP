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
