#include <benchmark/benchmark.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

std::vector<long> init() {
    std::vector<long> v;
    for (int i = 0; i < 1000; i++) {
        v.push_back(i);
    }
    return v;
}

const int SIZE = 200;

static void BM_truncate0(benchmark::State& state) {
    for (auto _ : state) {
        auto v = init();
        std::vector<long> v1(v.begin(), v.begin()+SIZE);
        v.swap(v1);
    }
}
BENCHMARK(BM_truncate0);

static void BM_truncate1(benchmark::State& state) {
    for (auto _ : state) {
        auto v = init();
        v.resize(SIZE);
        //v.shrink_to_fit();
    }
}
BENCHMARK(BM_truncate1);

static void BM_truncate2(benchmark::State& state) {
    for (auto _ : state) {
        auto v = init();
        std::vector<long> v1;
        for (int i = 0; i < SIZE; ++i) {
            v1.push_back(v[i]);
        }
        v.swap(v1);
    }
}
BENCHMARK(BM_truncate2);

BENCHMARK_MAIN();
