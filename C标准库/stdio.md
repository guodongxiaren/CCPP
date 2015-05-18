stdio.h
=======

strcpy() sprintf() strcat() 存在安全隐患， 其对应的安全版为： 
strncpy() snprintf() strncat()


###scanf、sscanf、fscanf
scanf的参数与sscanf、fscanf的后两个参数相同。

三个函数很像，唯一的区别就是输入源不同。  
scanf的输入源是标准输入，sscanf的输入源是指定的字符串，而fscanf的输入源是指的的输入流。  
所以scanf可以看作是第一个参数为stdin的fscanf