#include <type_traits>
#include <iostream>

using namespace std;

#define str(x) #x

#define eval(expr)  str(expr) << ": " << expr

struct A    // is_trivial = true
{
    int m;
};

struct B    // is_trivial = false
{
    int m;
    B()
    {}
};

struct C    // is_trivial = true
{
    int m;
    C() = default;
};
/* 
is_trivial: "平凡"，表示类型在默认构造，析构，拷贝，移动时不需要任何特殊操作
1.没有虚函数或虚基类。
2.由编译器生成默认的特殊成员函数，包括默认构造函数、拷贝构造函数、移动构造函数、赋值运算符、移动赋值运算符和析构函数。
3.数据成员同样需要满足条件 1 和 2。
 */

/*
is_pod == is_trivial && is_standard_layout
*/

int main(int argc, char ** argv)
{
    cout << boolalpha;
    // cout << is_trivial_v<char> << endl;
    cout << eval(is_trivial_v<A>) << endl;
    cout << eval(is_trivial_v<B>) << endl;
    cout << eval(is_trivial_v<C>) << endl;
    cout << eval(is_trivial_v<int>) << endl;
    cout << '\n';
    cout << eval(is_pod_v<A>) << endl;
    cout << eval(is_pod_v<int>) << endl;
    cout << '\n';
    cout << eval(is_fundamental_v<A>) << endl;
    cout << eval(is_fundamental_v<int>) << endl;
    cout << '\n';
    cout << eval(is_arithmetic_v<A>) << endl;
    cout << eval(is_arithmetic_v<int>) << endl;
    cout << '\n';
    cout << eval(is_scalar_v<A>) << endl;
    cout << eval(is_scalar_v<int>) << endl;
    cout << '\n';

    int n = 1;
    cout << eval(is_trivial_v<decltype(&n)>) << endl;
    cout << eval(is_fundamental_v<decltype(&n)>) << endl;
    cout << eval(is_arithmetic_v<decltype(&n)>) << endl;
    cout << eval(is_scalar_v<decltype(&n)>) << endl;

    // cout << is_trivial_v<B> << endl;
    // cout << is_trivial_v<double> << endl;
    // cout << is_trivial_v<uint64_t> << endl;

    A a1{1}, a2{1};

    // cout << (a1 == a2) << endl;

    return 0;
}