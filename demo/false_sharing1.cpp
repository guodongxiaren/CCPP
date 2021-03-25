#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
void foo(const vector<int> v, vector<long> sum, int id) {
    for (int i = 0; i < v.size(); ++i) {
        if (i%2 == id) {
            sum[id] += i;
        }
    }
    cout << "sum " << id << " = " << sum[id] << endl;
}

void foo2(const vector<int> v, vector<long> sum, int id) {
    long s = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (i%2 == id) {
            s += i;
        }
    }
    sum[id] = s;
    cout << "sum " << id << " = " << sum[id] << endl;
}
int main () {
    {
        vector<int> v;
        for (int i = 0; i < 100000; ++i) {
            v.push_back(i);
        }

        auto start = chrono::steady_clock::now();
        vector<long> sum = {0, 0};
        thread t1(foo, v, sum, 0);
        thread t2(foo, v, sum, 1);
        t1.join();
        t2.join();

        auto end = chrono::steady_clock::now();
        cout<< "block 1 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
    }
    cout << "----------" << endl;
    {
        vector<int> v;
        for (int i = 0; i < 100000; ++i) {
            v.push_back(i);
        }

        auto start = chrono::steady_clock::now();
        vector<long> sum = {0, 0};

        foo(v, sum, 0);
        foo(v, sum, 1);

        auto end = chrono::steady_clock::now();
        cout<< "block 2 cost:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
    }

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
