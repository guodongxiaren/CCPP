/*************************************************************************
	> File Name: pi.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年04月18日 星期六 02时29分17秒
 ************************************************************************/

#include <iostream>
#include <tbb/tbb.h>
using namespace std;
int main() {
    tbb::parallel_invoke(
        []() {cout<<"Hello"<<endl;},
        []() {cout<<"World"<<endl;}
        );
}

