string.h
============
##str开头
###strchr
查找字符串中某个字符首次出现的位置
```c
char *strchr(char *str,int ch)
```
返回首次出现字符ch的位置的指针，如果不存在返回NULL。
##b开头<kbd>deprecated</kbd>
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
* memcmp
* memmove

```c
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int   memcmp(const void *s1, const void *s2, size_t n);
```
