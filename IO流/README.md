I/O流
========
##文件流
- fstream
  - ifstream
  - ofstream

##ifstream
istream的子类

从文件读，由于历史原因，其参数是C风格字符串。

我们应该在流对象使用完成之后调用close函数关闭它，尽管在函数结束后，会自动调用它的析构函数（里面调用了close），
但是有时候因为是在缓冲区中，没有及时close，会导致丢失（我遇到过）。

```cpp
ifstream if("read.txt");

string str = "read.txt";
ifstream if2(str.c_str());

if.close();
if2.close();
```
也可以先声明，之后再用open函数指定要读的文件
```cpp
ifstream if;
if.open("read.txt");
```
如果要改变要读的文件，可以再次open，但是一定要保证close掉之前的文件。
```cpp
if.open("read.txt");
if.close();
if.open("hello.txt");
```
###设置偏移
使用成员函数seekg函数
```cpp
istream& seekg( streampos pos );  // 参数为整型，表示距离文件开始位置的偏移
istream& seekg( streamoff off, ios::seek_dir dir );
```
第二种重载形式的第二个参数表示相对位置：
|标志|说明|类比fseek
|---|----|------|
ios::beg | 文件开始的位置| SEEK_SET
ios::cur |当前位置| SEEK_CUR
ios::end | 文件末尾的位置| SEEK_END

##ofstream
ostream的子类。

大部分用法与ifstream相同。但也有不同：
###设置偏移
使用成员函数seekp函数。
```cpp
ostream& seekp( streampos pos );
ostream& seekp( streamoff off, ios::seek_dir dir );
```

##fstream
头文件
```cpp
#include <fstream>
```
fstream继承了ifstream和ofstream。可以进行读写。
```cpp
fstream if("read.txt"); //缺省是读模式
fstream of("write.txt", ios::out); //显式指定写模式
```
|其余标志|说明
|-----|-----
ios::app |从后面添加
ios::ate | 打开并找到文件尾
ios::binary | 二进制模式 I/O (与文本模式相对)
ios::in | 只读打开
ios::out | 写打开
ios::trunc | 将文件截为 0 长度（丢弃原来全部内容）

可以是按位或的组合。