#include <iostream>
#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include "debug.h"
#include "util/is_iterable.h"

int main() {
    std::cout << std::boolalpha;
    std::cout << eval(is_iterable<std::vector<int>>::value) << std::endl;  // true
    std::cout << eval(is_iterable<std::list<float>>::value) << std::endl;  // true
    std::cout << eval(is_iterable<int>::value) << std::endl;                // false
    
    std::cout << eval(is_iterable_v<std::vector<int>>) << std::endl;  // true
    std::cout << eval(is_iterable_v<std::list<float>>) << std::endl;  // true
    std::cout << eval(is_iterable_v<int>) << std::endl;                // false

    return 0;
}
