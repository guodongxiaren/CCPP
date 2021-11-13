#include <benchmark/benchmark.h>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

void split0(std::vector<std::string>& vec, std::string str, char delim) {
    std::stringstream ss(str);
    std::string word;
    while (std::getline(ss, word, delim)) {
        vec.push_back(word);
    }
}

void split1(std::vector<std::string>& vec, std::string str, char delim) {
    size_t pos = str.find(delim);
    while (pos != std::string::npos) {
        vec.emplace_back(str, 0, pos);
        std::string new_s = str.substr(pos+1);
        str.swap(new_s);
        pos = str.find(delim);
    }

    if (str.size() > 0) {
        vec.push_back(str);
    }
}

void split2(std::vector<std::string> &vec, std::string str, char delim) {
    size_t start = str.find_first_not_of(delim);
    size_t end;

    while (start != std::string::npos) {
        end = str.find_first_of(delim, start + 1);
        if (end == std::string::npos) {
            //vec.push_back(str.substr(start));
            vec.emplace_back(str, start);
            break;
        } else {
            //vec.push_back(str.substr(start, end - start));
            vec.emplace_back(str, start, end - start);
        }
        start = str.find_first_not_of(delim, end + 1);
    }
}


void split3(std::vector<std::string> &vec, std::string str, char delim) {
    int start = 0;
    while (start < str.size()) {
        size_t end = str.find(delim, start);
        if (end == std::string::npos) {
            vec.emplace_back(str, start);
            break;
        }
        vec.emplace_back(str, start, end-start);
        start = end + 1;
    }
}

/*
void string_view_split(std::vector<std::string_view> &vec, std::string str, char delim) {
    std::string_view sv(str);
    int start = 0;
    while (start < sv.size()) {
        size_t end = sv.find(delim, start);
        if (end == std::string::npos) {
            vec.emplace_back(sv.substr(start));
            break;
        }
        vec.emplace_back(sv.substr(start, end-start));
        start = end + 1;
    }
}
*/

void string_view_split2(std::vector<std::string> &vec, std::string str, char delim) {
    std::string_view sv(str);
    int start = 0;
    while (start < sv.size()) {
        size_t end = sv.find(delim, start);
        if (end == std::string::npos) {
            auto nsv = sv.substr(start);
            vec.emplace_back(nsv.data(), nsv.size());
            break;
        }
        auto nsv = sv.substr(start, end-start);
        vec.emplace_back(nsv.data(), nsv.size());
        start = end + 1;
    }
}

void strtok_split(std::vector<std::string> &vec, std::string str, char delim) {
    const int MAX_BUF_SIZE = 1024;
    char* save = NULL;
    char buf[MAX_BUF_SIZE];
    char del[2] = "";
    del[0] = delim;
    int ret = snprintf(buf, sizeof(buf), "%s", str.c_str());
    if (ret < 0) {
        return;
    }
    char* token = strtok_r(buf, del, &save);
    while (token != NULL) {
        vec.emplace_back(token);
        token = strtok_r(NULL, del, &save);
    }
}


const std::string global_str = "1234_56_890_abcd_efg_hijk_lmn_opq_rst_uvw_xyz_1111_222_444";


#define BM(func) static void BM_##func(benchmark::State& state) { \
    for (auto _ : state) { \
        std::vector<std::string> vec; \
        func(vec, global_str, '_'); \
    } \
} \
BENCHMARK(BM_##func);

BM(split0)
BM(split1)
BM(split2)
BM(split3)
BM(string_view_split2)
BM(strtok_split)


static void BM_boost_split0(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<std::string> vec;
        boost::split(vec, global_str, boost::is_any_of("_"));
    }
}
BENCHMARK(BM_boost_split0);

static void BM_boost_split1(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<std::string> vec;
        boost::split(vec, global_str, [](char c) {return c == '_';});
    }
}
BENCHMARK(BM_boost_split1);



BENCHMARK_MAIN();
/*

int main() {
    std::string s = "xxx_xxx_333_dd_e";
    std::vector<std::string> vec;
    strtok_split(vec, s, '_');
    //split3(vec, s, '_');
    for (auto w: vec) {
        std::cout << w<< "#"<<std::endl;
    }
}
*/
