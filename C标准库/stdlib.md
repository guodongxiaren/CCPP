stdlib.h
========
##数值类型转换
|函数名|
|----|
|atof|
|atoi|
|atol|
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
