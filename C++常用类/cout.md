cout及其操纵符
=====
##操纵符
cout本身没有五花八门的输出方式，改变它的输出行为是通过使用操纵符（操纵函数）的方式完成的。  

操纵函数包含在头文件`<iomanip>`中，manip是manipulator（操纵器）的缩写。
##操纵符的使用
将操纵函数直接丢到<<符号后面即可。  
比如：`cout<<setioflag(ios::left);`用来设置左对齐。
###常用操纵符
|操纵符|描述|操纵符|描述
|-----|----|-----|-----
|dec|十进制|setiosflags(ios::fixed)|定点格式显示
|hex|十六进制|setiosflags(ios::left)|左对齐
|oct|八进制|setiosflags(ios::right)|右对齐
|setfill(`c`)|设置填充字符c|setiosflags(ios::skipws)|忽略前导空格
|setprecision(`n`)|设置小数精度为n位|setiosflags(ios::uppercase)|十六进制数大写输出
|setw(`n`)|设域宽为n个字符|setiosflags(ios::lowercase)|十六进制数小写输出

注意
- 十六进制显示是缺省是显示小写字母的 
- ios::fixed是将浮点数表示为整数+小数点+小数部分的格式，小数位数为6。缺省为5位。
- setprecision(2)时则12.123显示为12.12，而setprecision(0)时为默认小数长度，不截断
- 操纵符可以混合使用，用多个<<间隔
- 一个cout中可以中途改变输出方式，数据输出的时候其格式以其前面的操纵符为准
- 操纵符是全局的，即使是写了多个cout，不同的cout之间其输出方式也是共同的。

一个栗子：
```cpp
double pi = 3.14125926;
cout<<pi<<endl;
cout<<setprecision(0)<<pi<<endl
    <<setprecision(2)<<pi<<endl
	<<setprecision(4)<<pi<<endl;
cout<<pi<<endl;
```
输出：
```
3.14159
3
3.14
3.1416
3.1416
```
