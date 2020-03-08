#include <iostream>
#include <map>
#include <list>
#include <set>
#include <string>
#include <vector>
struct has_push_back {

    template <typename C, void (C::*)(const typename C::value_type&)>
    struct Helper;

    template <typename C, void (C::*)(typename C::value_type)>
    struct Helper2;

    template <typename C>
    static bool test(...) {
        return false;
    }
    template <typename C>
    static bool test(Helper<C, &C::push_back>*) {
        return true;
    }
    template <typename C>
    static bool test(Helper2<C, &C::push_back>*) {
        return true;
    }
};

int main() {
    std::cout << has_push_back::test<std::list<int> >(NULL) << std::endl;
    std::cout << has_push_back::test<std::map<int, int> >(NULL) << std::endl;
    std::cout << has_push_back::test<std::set<int> >(NULL) << std::endl;
    std::cout << has_push_back::test<std::string>(NULL) << std::endl;
    std::cout << has_push_back::test<std::vector<int> >(NULL) << std::endl;
    return 0;
}

