#include <iostream>
#include "util/rand.hpp"

using namespace std;

int main()
{
    for(int i = 0; i < 10; i++)
        cout << probe::rand(0, 10) << ' ';
    cout << endl;

    for(int i = 0; i < 10; i++)
        cout << probe::rand(0, 10) << ' ';
    cout << endl;

    for(int i = 0; i < 10; i++)
        cout << probe::rand(0.0, 1.0) << ' ';
    cout << endl;

    for(int i = 0; i < 10; i++)
        cout << probe::rand(0.0, 1.0) << ' ';
    cout << endl;

    default_random_engine e(time(0));
    bernoulli_distribution d;
    for(int i = 0; i < 10; i++)
        cout << d(e) << ' ';
    cout << endl;

    return 0;
}