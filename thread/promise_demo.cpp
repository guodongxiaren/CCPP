#include <iostream>
#include <future>
#include <string>
#include <thread>

#include <unistd.h>

int main() {
    auto on_work = [](int num, std::promise<std::string> p) {
        sleep(5);
        if (num % 2) {
            p.set_value("奇数");
        } else {
            p.set_value("偶数");
        }
        return; 
    };
    std::promise<std::string> p;
    std::future<std::string> f = p.get_future();
    
    int t = (int)time(NULL);
    std::thread th(on_work, t, std::move(p));
    std::cout << t << " 是" << f.get() << std::endl;
    th.join();

    return 0;
}

