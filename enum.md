枚举类型
=========
##声明
比如：
```c
//weekday是枚举类型名
enum weekday
{
    sun,mon,tue,wed,thu,fri,sat
};
```
注意:
* 最后枚举元素后面是**没有分号的**
* 枚举元素不是字符串，不要加引号

##定义
###先声明后定义
```c
//定义一种名为enum_type的枚举类型
enum enum_type
{
    ....
};
//C语言
enum enum_type a,b,c;
//C++
enum_type a,b,c;
```
###声明的同时定义
```c
enum enum_type
{
    ....
}a,b,c
```
###直接定义
```c
enum
{
    ....
}a,b,c
```
##枚举的值
###缺省的值
枚举类型的值其实也是整数，默认从0开始迭代的值。  
比如：
```cpp
//C++语法
weekday w[7];
w[0] = sun;
w[1] = mon;
w[2] = tue;
w[3] = wed;
w[4] = thu;
w[5] = fri;
w[6] = sat;
for(int i=0;i<7;i++)
{
    cout<<w[i]<<" ";
}
```
打印结果是：`0 1 2 3 4 5 6`  
尽管如此，如果直接给枚举类型的变量赋整型值，是不对的。不过可以进行强制类型转换。比如：
```c
//C
enum weekday a;
a = (enum weekday)2;
```
###显示定义
```c
enum season
{
    spring=5,summer=1,autumn,winter
};
```
此时autumn和winter是在summer（其值为1）的基础上顺序加1。
}
##匿名枚举
当声明枚举却没有给出该枚举的名称的时候，其实它的效果仅仅相当于简便的常量定义方式。比用`#define`定义常量要简单，但有人争议这样做可读性差。
