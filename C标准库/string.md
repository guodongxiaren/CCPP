string.h
============
str开头
--------
###strchr
查找字符串中某个字符首次出现的位置
```c
char *strchr(char *str,int ch)
```
返回首次出现字符ch的位置的指针，如果不存在返回NULL。
###strcpy和strdup
都是复制字符串，不过strcpy是复制到栈中，而strdup是分配一个堆内存来存储，返回其首地址，用free函数释放。


b开头<kbd>deprecated</kbd>
-------------------
b开头的这几个函数只在gcc中有，VC中不存在。并且最新的POSIX标准不推荐使用这几个函数了，应该用mem系列函数来替代。
* bzero：用memset来替代
* bcopy：用memcpy或memmove来替代
* bcmp：用memcmp来替代

```c
void bzero(void *s,int n);
void bcopy(const void *src, void *dest, int n);
void bcmp(const void *s1, const void *s2, int n);
```
bcopy与memcpy的功能相同但参数顺序不同，memcpy的参数顺序记忆的时候可以联想a=b。目的指针在，源指针在后。而bcopy正好相反。  
bcmp是比较s1和s2的前n个字节是否相等。如果s1==s2或n=0则返回零，否则返回非零值。bcmp不检查NULL。
##mem开头
* memset
* memcpy
* memmove
* memcmp

```c
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int   memcmp(const void *s1, const void *s2, size_t n);
```
###memset
从s位置开始填充n个字节c。但c是一个整型，实际上c等于0和-1的时候，能把字节清空成0和-1。 
###memcpy&memmove
memcpy和memmove完成的功能都是从src复制n个字节到dest位置。但是如果src要拷贝的内存区域与dest有重叠，那么memcpy的处理结果是不确定的，但是memmove能保证正确复制。  
>另有**memccpy**函数。

###memcmp
如果s1的前n个字节和s2的前n个字节相比，从左到右逐个比较，返回第一个不相同的字节的差值（s1-s2）。
