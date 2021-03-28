#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
const int N = 10000; // vector v 大小
const int M = 2;     // vector sum 大小
void foo(const vector<int>& v, vector<long>& sum, int id) {
    //cout << "id:" << id << &sum << " " << &v << endl;
    for (int i = 0; i < v.size(); ++i) {
        if (i%M == id) {
            sum[id] += i;
        }
    }
    cout << "sum " << id << " = " << sum[id] << endl;
}

void foo2(const vector<int>& v, vector<long>& sum, int id) {
    //cout << "id:" << id << &sum << " " << &v << endl;
    long s = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (i%M == id) {
            s += i;
        }
    }
    sum[id] = s;
    cout << "sum " << id << " = " << sum[id] << endl;
}
int main () {
    vector<int> v;
    for (int i = 0; i < N; ++i) {
        v.push_back(i);
    }

    {   // 代码块 1
        vector<long> sum(M, 0);
        auto start = chrono::steady_clock::now();
        vector<thread> td;
        for (int i = 0; i < M; ++i) {
            td.emplace_back(foo, std::cref(v), std::ref(sum), i);
        }
        for (int i = 0; i < M; ++i) {
            td[i].join();
        }
        auto end = chrono::steady_clock::now();
        cout<< "block 1 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
    }
    cout << "----------" << endl;
    {   // 代码块2
        vector<long> sum(M, 0);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < M; ++i) {
            foo(v, sum, i);
        }
        auto end = chrono::steady_clock::now();
        cout<< "block 2 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
    }
    cout << "----------" << endl;
    {   // 代码块 3
        vector<long> sum(M, 0);
        auto start = chrono::steady_clock::now();
        vector<thread> td;
        for (int i = 0; i < M; ++i) {
            td.emplace_back(foo2, std::cref(v), std::ref(sum), i);
        }
        for (int i = 0; i < M; ++i) {
            td[i].join();
        }
        auto end = chrono::steady_clock::now();
        cout<< "block 3 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
    }

    cout<<sizeof(int) <<endl;
}
/*
 * sum 0 = 2499950000
 * sum 1 = 2500000000
 * block 1 cost:13678
 * ----------
 *  sum 0 = 2499950000
 *  sum 1 = 2500000000
 *  block 2 cost:1138
 */
