#include <iostream>
#include <tuple>
#include <functional>
#include <pthread.h>
using namespace std;
// clang++ -std=c++11 -pthread pthread_create_cpp.cpp

void echo(const std::string& str) {
    cout<<"---"<<endl;
    cout<<str<<endl;
}

template<class Fn, class... Args>  
void gthread(pthread_t* th, pthread_attr_t* attr, Fn&& fn, Args&&...args) {

    auto l = new auto([=]{ fn(args...);  });
    auto te = [](void* ar) ->void* {
        auto f = reinterpret_cast<decltype(l)>(ar);
        (*f)();
        delete f;
        return nullptr;

    };
    pthread_create(th, attr, te, l);
}
    
struct A {

    void* operator()(void*) {
        cout<<"xxxx"<<endl;
        return nullptr;
    }
};
int main()
{
    pthread_t th; 
    gthread(&th, NULL, echo, "hello world");

    pthread_join(th, NULL);

    pthread_t t; 
    A a;
    a(NULL);
    //pthread_create(&t, NULL, a, NULL);
    //pthread_join(t, NULL);
    return 0;
}

