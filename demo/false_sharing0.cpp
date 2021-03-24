#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
void foo(const vector<int> v, vector<long> sum, int id) {
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < v.size(); ++i) {
        if (i%2 == id) {
            sum[id] += i;
        }
    }
    auto end = chrono::steady_clock::now();
    cout << "sum " << id << " = " << sum[id] << endl;
    cout<< "t1 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
}

void foo2(const vector<int> v, vector<long> sum, int id) {
    auto start = chrono::steady_clock::now();
    long s = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (i%2 == id) {
            s += i;
        }
    }
    sum[id] = s;
    auto end = chrono::steady_clock::now();
    cout << "sum " << id << " = " << sum[id] << endl;
    cout<< "t2 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
}
int main () {
    vector<int> v;
    for (int i = 0; i < 100000; ++i) {
        v.push_back(i);
    }
    vector<long> sum = {0, 0};
    thread t1(foo, v, sum, 0);
    thread t2(foo, v, sum, 1);
    t1.join();
    t2.join();

    cout << "----------" << endl;
    vector<long> sum1 = {0, 0};
    thread t3(foo2, v, sum1, 0);
    thread t4(foo2, v, sum1, 1);
    t3.join();
    t4.join();
}
