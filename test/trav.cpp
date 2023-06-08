#include <iostream>
#include <forward_list>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include "util/is_iterable.h"

using namespace std;

template<typename Container, std::enable_if_t<is_iterable_v<Container>>* = nullptr>
void trav(Container c)
{
    cout << "distance: " << distance(c.begin(), c.end()) << '\n';
    auto it = c.begin(), end = c.end();
    while(it != end)
    {
        it++;
    }
}

int main(int argc, char ** argv)
{
    vector<int> nums(100);
    string s = __FUNCTION__;
    forward_list<int> fl(70);
    trav(nums);
    trav(s);
    trav(fl);

    return 0;
}