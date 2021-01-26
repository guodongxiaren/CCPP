/*************************************************************************
	> File Name: truncate.cpp
	> Author: 
	> Mail: 
	> Created Time: 2021年01月26日 星期二 21时41分24秒
 ************************************************************************/

#include <algorithm>

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/time.h>

using namespace std;

// 无返回值f
template<typename F, typename V> 
void test(F f, V& v) {
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);
    f(v);
    gettimeofday(&t2, NULL);
    long long timeuse = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);
    printf("time cost:%lld\n", timeuse);
}

// 有返回值f
template<typename F, typename V> 
void test2(F f, V& v) {
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);
    V v1 = f(v);
    gettimeofday(&t2, NULL);
    long long timeuse = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);
    printf("time cost:%lld\n", timeuse);
}

std::vector<long> init() {
    std::vector<long> v;
    v.clear();
    for (int i = 0; i < 100000; i++) {
        v.push_back(i);
    }
    return v;
}

int main() {
    const int SIZE = 200;
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            std::vector<long> v1(v.begin(), v.begin()+SIZE);
        };
        test(fun, v);
    }
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            std::vector<long> v1(v.begin(), v.begin()+SIZE);
            v1.swap(v);
        };
        test(fun, v);
    }
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            std::vector<long> v1(v.begin(), v.begin()+SIZE);
            v1.swap(v);
            return v1;
        };
        test2(fun, v);
    }
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            v.resize(SIZE);
        };
        test(fun, v);
    }
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            v.resize(SIZE);
            v.shrink_to_fit();
        };
        test(fun, v);
    }
    {
        auto v = init();
        auto fun = [](std::vector<long>& v) {
            std::vector<long> v1;
            for (int i = 0; i < SIZE; ++i) {
                v1.push_back(v[i]);
            }
            v.swap(v1);
        };
        test(fun, v);
    }

}
