stdlib.h
========
##数值类型转换
|函数名|
|----|
|atof|
|atoi|
|atol|
|strtod|
|strtol|
|strtoul|
###atof
函数名的含义是`ascii to float`。将字符串（char *）转换为浮点型（double）。 
```c
double atof(const char *s)
``` 
该函数会忽略掉前导空白符。如果该字符串不是合法字符串，程序不会报错。有如下两种情形：
* 在合法字符串的末尾有非法字符，如"123.123abc"。编译器会直接忽略末尾的非法字符，返回值123.123000
* 在合法字符串的其他位置有非法字符，该函数会返回0.000000

###atoi
```c
int atoi(const char *s)
``` 
将字符串（char *）转换为整型（int）。
如果字符串s，中包含小数则直接忽略小数点之后的部分。其他注意事项同atof。
```c
char *s1="123.123";
char *s2="123.123abc";
char *s3="abc123";

printf("%d\n",atoi(s1)); //输出123
printf("%d\n",atoi(s2)); //输出123
printf("%d\n",atoi(s3)); //输出0
```
###atol
```c
long atol(const char *s)
``` 
将字符串（char *）转换为长整型（long）。注意事项同aoti函数。
###strtod
```c
double strtod(const char *s,char **endp)
```
将字符串转换为浮点型，将不能转换的部分存到endp中。
比如：
```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *s="123.123abc";
	char *endp; 
	double d = strtod(s,&endp);

	printf("%f  %s\n",d,endp);//输出123.123  abc
}
```
>atoi(s)相当于strtod(s,NULL)

###strtol
```c
long strtol(const char *s,char **endp,int base)
```
将字符串s转换为长整型，未转换的部分保存到endp。base是假定的s的基底。即字符串s描述的是一个base进制的数。  
base的取值范围为：
* 0 （视作十进制）
* 2<=base<=36

###strtoul
```c
unsigned long strtoul(const char *s,char **endp,int base)
```
与strtol类似，只不过转换后的类型是unsigned long类型。