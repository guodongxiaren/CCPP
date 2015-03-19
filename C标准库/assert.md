assert.h
======
定义了宏`assert`（断言）。  
##格式
```c
	assert(int类型表达式);
```
如果表达式为假（0），则assert宏就按照实现定义的格式向标准错误写入失败信息，然后调用`abort()`函数。如果表达式为真，则什么都不做。
##NDEBUG宏
如果定义了NDEBUG宏，则assert不起作用。一般在程序调试完成之后正式发布的时候需要禁掉assert，可选的方式有两种。
1. 在程序开头加入`#define NDEBUG`
2. 给编译器添加宏参数。如`CC -DNDEBUG 文件名`


