#include <type_traits>
#include <iterator>
#include <iostream>
#include <vector>
#include <forward_list>
#include <map>
#include <list>
#include "debug.h"

using namespace std;

#define eval(expr) str(expr) ": " << expr

int main(int argc, char ** argv)
{
    cout << boolalpha;
    using n1 = iterator_traits<vector<int>::iterator>::iterator_category;
    using n2 = iterator_traits<forward_list<int>::iterator>::iterator_category;
    using n3 = iterator_traits<map<char *, int>::iterator>::iterator_category;
    using n4 = iterator_traits<list<int>::iterator>::iterator_category;

    cout << is_base_of_v<input_iterator_tag, input_iterator_tag> << endl;
    cout << is_base_of_v<input_iterator_tag, n1> << endl;
    cout << is_base_of_v<input_iterator_tag, n2> << endl;
    cout << is_base_of_v<input_iterator_tag, n3> << endl;
    cout << is_base_of_v<input_iterator_tag, n4> << endl;

    return 0;
}