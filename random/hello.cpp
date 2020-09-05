#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 mt(rd()); // 随机种子，生成序列不同

    //std::mt19937 mt(1729); // 确定的种子，生成序列相同

    std::uniform_int_distribution<int> dist(0, 99); // 包含0和99
    for (int i = 0; i < 16; ++i) {
        std::cout<<dist(mt)<<std::endl;
    }
    std::cout<<"-------"<<std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout<<dist(rd)<<std::endl;
    }
    return 0;
}

