#include "util/eq.h"
#include <iostream>
#include <vector>
#include "debug.h"

using std::cout, std::endl;

int main()
{
    cout << std::boolalpha;

    int n = 2;
    int &rn = n;

    cout << eval(probe::__eq__(1, 1)) << endl;
    cout << eval(probe::__eq__(n, 1)) << endl;
    cout << eval(probe::__eq__(n, n)) << endl;
    // cout << eval(probe::__eq__(&n, n)) << endl; // 左右类型不匹配，编译失败
    cout << eval(probe::__eq__(&n, &n)) << endl;
    cout << eval(probe::__eq__(rn, n)) << endl;
    cout << eval(probe::__eq__(&rn, &n)) << endl;
    // cout << eval(probe::__eq__(nullptr, NULL)) << endl; // 左右类型不匹配
    cout << eval(probe::__eq__(nullptr, nullptr)) << endl;

    std::vector<int> nums1 = {1, 2, 3, 4, 5}, nums2 = {1, 2, 3}, nums3(nums2);
    cout << eval(probe::__eq__(nums1, nums2)) << endl;
    cout << eval(probe::__eq__(nums2, nums3)) << endl;
    auto aaaa = {1, 2, 3};
    cout << eval(probe::__eq__(aaaa, aaaa)) << endl;

    return 0;
}