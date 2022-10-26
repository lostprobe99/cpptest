#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;

int main(int argc, char ** argv)
{
    ofstream of("out.txt", ios::out);
    auto start = system_clock::now();
    for(int i = 0; i < 1e4; i++)
        of << i << '\n';
        // cout << i << '\n';

    auto end = system_clock::now();
    cout << duration_cast<milliseconds>(end - start).count() << '\n';

    return 0;
}