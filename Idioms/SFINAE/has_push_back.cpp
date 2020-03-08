#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
class Base {

};
class Drive:Base {
public:
    void hello() {}
};
template <typename T>
struct has_hello {
    typedef char Yes[1];
    typedef char No[2];

    template <typename>
    static No& has(...);

    template <typename C>
    static Yes& has(decltype(&C::hello));

    static const bool value = sizeof(has<T>(NULL)) == sizeof(Yes);
};
/* 失败案例一
template <typename T>
struct has_push_back {
    typedef char Yes[1];
    typedef char No[2];

    template <typename>
    static No& has(...);

    template <typename C>
    static Yes& has(decltype(&C::push_back));

    static const bool value = sizeof(has<T>(NULL)) == sizeof(Yes);
};
*/

/* 失败案例二
template <typename>
using void_t = void;

template <typename T, typename V = void>
struct has_push_back:std::false_type {};

template <typename T>                         
struct has_push_back<T, void_t<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>>:std::true_type {};
*/

template <typename T>
struct has_push_back {

  using yes = char[1];
  using no  = char[2];

  template <typename U>
  static constexpr yes& test(decltype(std::declval<U>().push_back(std::declval<typename U::value_type>())));
  template <typename U>
  static constexpr yes& test(decltype(std::declval<U>().push_back(std::declval<const typename U::value_type&>())));

  template <typename>
  static constexpr no& test(...);

  static constexpr bool value = (sizeof(yes) == sizeof(test<T>(nullptr)));

}; 



int main() {
    std::cout << has_hello<Base>::value << std::endl;
    std::cout << has_hello<Drive>::value << std::endl;

    std::cout << has_push_back<std::list<int> >::value << std::endl;
    std::cout << has_push_back<std::map<int, int> >::value << std::endl;
    std::cout << has_push_back<std::set<int> >::value << std::endl;
    std::cout << has_push_back<std::string>::value << std::endl;
    std::cout << has_push_back<std::basic_string<char> >::value << std::endl;
    std::cout << has_push_back<std::vector<int> >::value << std::endl;
    return 0;
}


