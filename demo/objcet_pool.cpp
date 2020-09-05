/*************************************************************************
	> File Name: objcet_pool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年09月05日 星期六 13时23分30秒
 ************************************************************************/

#include <algorithm>
using namespace std;

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

template <class T>
class ObjectPool {
public:
    using create_obj_t = std::function<T*()>;
    using clear_obj_t = std::function<void(T*)>;

    ObjectPool(create_obj_t create_fun, clear_obj_t clear_fun):_create_fun(create_fun),_clear_fun(clear_fun) {
    }

    int init() {
        for (int i = 0; i < _pool_max_size; ++i) {
            T* t = _create_fun();
            push(std::shared_ptr<T>(t));
        }
    }

    std::shared_ptr<T> get() {
        return pop();
    }
    int put(std::shared_ptr<T> p_obj) {
        _clear_fun(p_obj.get());
        push(p_obj);
    }
protected:
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_pool.empty()) {
            return nullptr;
        }
        auto p_obj = _pool.front();
        printf("pop %p index:%d\n", p_obj.get(), _pool.size());
        _pool.pop();
        return p_obj;
    }

    int push(std::shared_ptr<T> p_obj) {
        std::lock_guard<std::mutex> lock(_mutex);
        printf("push %p index:%d\n", p_obj.get(), _pool.size());
        _pool.push(p_obj);
    }


private:
    std::queue<std::shared_ptr<T>> _pool;
    std::mutex _mutex;
    int _pool_max_size = 2; 
    create_obj_t _create_fun;
    clear_obj_t _clear_fun;
};

class A {
public:
    A() {
        std::cout<<"create xxx"<<std::endl;
    }
    void clear() {
        std::cout<<"clear xxx"<<std::endl; 
    }
    void echo() {
        printf("this is:%p\n", this);
    }

};
int main() {
    constexpr auto create_A = [](){return new A;};
    constexpr auto clear_A = [](A* a){if (a!=nullptr) a->clear();};
    ObjectPool<A> op(create_A, clear_A);
    op.init();
    auto pt = op.get();
    pt->echo();
    auto pt1 = op.get();
    if (pt1!=nullptr) {
        pt1->echo();
    }
    auto pt2 = op.get();
    if (pt2!=nullptr) {
        pt2->echo();
    } else {
        printf("error\n");
    }
    op.put(pt);
    auto pt3 = op.get();
    if (pt3!=nullptr) {
        pt3->echo();
    } else {
        printf("error\n");
    }
}
