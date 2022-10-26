#include <type_traits>
#include <iostream>

using namespace std;

int main()
{
    cout << is_convertible<int, double>::value << endl;
    cout << is_convertible_v<int, double> << endl;

    return 0;
}