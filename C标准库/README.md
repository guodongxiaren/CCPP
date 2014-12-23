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
|[stdlib.h][stdlib]|

-------
stdlib:stdlib.md