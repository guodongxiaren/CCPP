string.h
============
##str开头
###strchr
查找字符串中某个字符首次出现的位置
```c
char *strchr(char *str,int ch)
```
返回首次出现字符ch的位置的指针，如果不存在返回NULL。
##b开头
b开头的这几个函数只在gcc中有，VC中不存在
* bzero
* bcopy
* bcmp

```c
void bzero(void *s,int n);
void bcopy(const void *src, void *dest, int n);
void bcmp(const void *s1, const void *s2, int n);
```
最新的POSIX标准不建议使用bzero，推荐用memset来替换它。  
bcmp是比较s1和s2的前n个字节是否相等。如果s1==s2或n=0则返回零，否则返回非零值。bcmp不检查NULL。
##mem开头
* memset
* memcpy
* memcmp
* memmove

bcopy和memcpy功能相同，但是参数的顺序不同。
