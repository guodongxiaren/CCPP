##占位符
|%|对应类型|
|---|----
|d|int
|c|char 
|s|char *
|f|float,double
|p|指针类型
|lf|double
|lu|unsigned long
>在printf的时候double类型可以用%f或%lf。而scanf的时候double要用%lf

当用%p输出指针地址的时候，格式是**0x**加上十六进制地址值。如果为空指针则打印**(nil)**。  
###格式化串 "%a.bs"  
- 对于a,它表示如果字符串长度小于a,那么右对齐左边补空格，若大于a则原样输出不限制
- 对于b，它表示如果字符串长度超过b，那么只取前b个

##参数压栈顺序
printf的参数压栈顺序是从右到左的，所以：
```c
	char a[] = "abcde";
	char *p = a;
	printf("%c %c\n",*p,*(++p));
```
打印结果为：`b b`
##Trick
###printf("5432"+1)
这条语句看似无理，实则有理。输出是**432**。  
"5432"是一个字符串。+1就是指针位置+1。相当于：
```c
char a[] = "5432";
printf("%s",a+1);
```
