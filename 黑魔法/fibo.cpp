/*************************************************************************
	> File Name: fibo.cpp
	> Author: guodongxiaren
	> Created Time: Mon Dec 27 22:24:50 2021
    > Description:
      编译期间做斐波那契数列求值
      斐波那契数列：1 1 2 3 5 8 13 21 34
      F(i) = F(i-1) + F(i-2)
 ************************************************************************/

#include <iostream>
using namespace std;
template<int i>
class F {
public:
    constexpr static int foo() {
        return F<i-1>::foo() + F<i-2>::foo();
    }
};
template<>
class F<0> {
public:
    constexpr static int foo() {
        return 0;
    }
};
template<>
class F<1> {
public:
    constexpr static int foo() {
        return 1;
    }
};
template<>
class F<2> {
public:
    constexpr static int foo() {
        return 2;
    }
};
int main() {
    cout << F<1>::foo() <<endl;
    cout << F<2>::foo() <<endl;
    cout << F<3>::foo() <<endl;
    cout << F<4>::foo() <<endl;
    cout << F<5>::foo() <<endl;
    cout << F<6>::foo() <<endl;
    cout << F<7>::foo() <<endl;
    cout << F<8>::foo() <<endl;
}
