宏定义
=======
在编译期间宏的内容被展开（替换）   
##空宏定义
如果只定义了宏名，宏名后面为空，则代码中出现该宏的位置，在编译期间会之间削掉这个宏。
```c
#define XXX
main(){
    printf(XXX"hello world\n");
}
```
使用`gcc -E`查看一下，可以发现：
```c
    printf("hello world\n");
```
## **#**
不管是#还是##都是配合宏函数来使用的，如下的用法是错的：
```c
#define PORT #80
```
这并不会把80变成字符串"80"
## **#**
一个井号`#`是字符串化的意思。所谓字符串化，就是将**符号**转化为字符串。  
比如：
```c
#include <stdio.h>

#define PRINT(x) printf(#x" 的值是 %s\n",x)
#define PRINT2(x) printf("x 的值是 %s\n",x)
int main()
{
	char * var = "hello world";
	PRINT(var); //打印var的值是 hello world
	PRINT2(var);//打印x的值是 hello world
}
```
上面例子将参数字符串化
>上面的例子中不能将#x写进引号之中，即*printf(#x" 的值是 %s\n",x)*，否则将打印#x 的值是 hello world。  
也不能将x的值写到引号外面，即printf(x" 的值是 %s\n",x)，这样会保错，因为prinf的第一个参数必须是字符串。 

## **##**
两个井号`##`，用作宏定义中，起**连接符**的作用。
是将左右两边的字符连接到一起，注意这里连接之后生成的是**符号**，而不是字符串。  
比如：
```c
#include <iostream>
#define TEST(c) test##c
int main()
{
	int test1=123;
	std::cout<<TEST(1)<<std::endl;
}
```
可以正确打印出变量test1的值。
>所谓符号，不是字符串，而是指的变量名，类型名，函数名、宏名等等。

更有趣的例子是：
```c
#include <iostream>
#define TEST(c) test[##c]
int main()
{
	int test[10];
	for(int i=0;i<10;i++)
		test[i]=i;
	for(int i=0;i<10;i++)
		std::cout<<TEST(i)<<std::endl;
}
```
