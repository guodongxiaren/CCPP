C语言标准库
============
所谓标准库，即非第三方库，并且是平台无关的  
C++在包含C语言的标准库头文件的时候，习惯做法是去掉`.h后缀`，并且加上`c前缀`。
如：
```cpp
//C语言中
#include <stdlib.h>
#include <string.h>

//C++中包含C语言标准库头文件
#include <cstdlib>
#include <cstring>
```
##目录索引
|头文件|描述|
|-------|-----
|[stdlib.h](stdlib.md)|
|[stdio.h](stdio.md)|
|[stdarg.h](stdarg.md)|
|[string.h](string.md)|

-------
##数据类型
`size_t`是为了提高程序可移植而定义在标准C中的，其实就是`unsigned int`。  
`ssize_t`是Unix系统中定义的，表示`signed size_t`,实际可以理解为`int`。
