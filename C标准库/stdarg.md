stdarg.h
===========
定义了可变参数列表的函数声明方式
##基本内容
“四”个宏一个类型
###重要的宏
- va_start
- va_arg
- va_end
- va_copy(C99,C++11)

###类型
va_list
##用法
可变参数列表的函数必须至少有一个是固定参数。
```c
va_list ap;
```
声明一个可变参数列表。
```c
void va_start(va_list ap,last_arg);
```
初始化参数列表ap（供`va_arg`和`va_end`调用），last_arg是固定参数的最后一个参数。
```c
type va_arg(va_list ap,type);
```
每执行一次就，就指向可变参数列表的下一个参数。比如：  
```c
va_list ap;
va_start(ap,n);
int a;
while(n--){
    a = va_arg(ap,int);
    ...
}
```
>但是可变参数列表并没有显式的标识表示参数结束，printf也是根据固定参数字符串中的%个数，来判断后面可变参数的个数的。
>>所以可变参数的函数声明中必须至少有一个是固定参数，借此可以的指明（或推导出）可变参数的个数。

```c
void va_end(va_list ap);
```
##函数
```c
int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```
以上函数参数中的format和printf的第一个参数相同，最后一个参数ap就是可变参数。它们的主要区别是输出位置不同。
