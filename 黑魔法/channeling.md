Channeling技巧
============
```c
void declare()
{
    int a[100];
	int i;
	for (i = 0; i < 100; i++)
	    a[i] = i+1;
}
void print()
{
    int a[100];
	int i;
	for (i = 0; i< 100; i++)
	    printf("%d ", a[i]);
}
int main()
{
    declare();
	print();
}
```
以上代码能够正确打印出1到100这些数字。  

其原因是，函数调用结束式sp指针回到调用函数前的位置。函数sp所指位置下面的内存内容并不会被清空。