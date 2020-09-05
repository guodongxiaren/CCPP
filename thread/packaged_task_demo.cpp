#include <iostream>
#include <future>
#include <string>
#include <thread>

#include <unistd.h>
std::string on_work(int num) {
    //sleep(5);
    if (num % 2) {
        return "奇数";
    } else {
        return "偶数";
    }
};

int main() {
    std::packaged_task<std::string(int)> task(on_work);
    std::future<std::string> f = task.get_future();
    
    int t = (int)time(NULL);
    std::thread th(std::move(task), t);
    std::cout << t << " 是" << f.get() << std::endl;
    th.join();

    return 0;
}

