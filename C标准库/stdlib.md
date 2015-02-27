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

数值计算
--------
|函数名|描述
|------|----
|abs|求int型绝对值
|labs|求long型绝对值
|div|int型除法，保留商和余数
|ldiv|long型除法，保留商和余数

###abs
```c
int abs(int n)
```
求绝对值。同理还有用于长整型取整的**labs**函数。
###div
```c
div_t div(int num,int denom)
```
参数：
* num是被除数
* denom是除数

商是div_t类型。
```c
/* 在stdlib.h头文件中定义 */
typedef struct
{
    int quot;  //商
    int rem;   //余数
}div_t;
```
同理还有用于长整型除法的**ldiv**函数，它的返回值类型为**ldiv_t**。
算法相关
--------
###rand
```c
int rand()
```
通常不单独使用，需要使用srand函数设置随机数种子。
实际是伪随机数，如果设置的种子相同，则随机数产生的数字序列可以认为固定了。
###srand
```c
void srand(unsigned int seed)
```
其参数为新的随机数序列的种子。这个序列后来对rand的调用返回。通常以时间为种子,这样可以避免种子相同。
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    srand((unsigned)time(NULL));
    for(i=0;i<MAX;i++)
    {
        printf("%d",rand()%100);
    }
}
```
##内存管理
|函数名|描述
|----|----
|malloc|分配内存
|calloc|分配内存
|realloc|重新分配内存
|free|释放内存
###realloc
```c
void *realloc(void *ptr, size_t size);
```
对指定的指针（ptr）重新申请分配大小为size的空间，返回指向分配内存的地址指针。  
- 如果原ptr处有足够的空间可分配，那么返回的指针和ptr相同
- 如果原ptr处没有足够的空间可分配（或者ptr是空指针），那么系统会在堆上重新找一块大小为size的内存，并返回该处的地址指针
- 分配内存失败，返回空指针NULL

