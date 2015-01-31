##占位符
|%|对应类型|
|---|----
|d|int
|c|char 
|s|char *
|f|float,double
|lf|double
|lu|unsigned long
>在printf的时候double类型可以用%f或%lf。而scanf的时候double要用%lf

###格式化串 "%a.bs"  
- 对于a,它表示如果字符串长度小于a,那么右对齐左边补空格，若大于a则原样输出不限制
- 对于b，它表示如果字符串长度超过b，那么只取前b个
