#include <iostream>

struct fib_frame {
    int state = 0;
    int a, b, c;
};

int co_fib(fib_frame &f)
{
    switch(f.state)
    {
        case 0:
            f.state = 1;
            goto s0;
        case 1:
            f.state = 2;
            goto s1;
        case 2:
            f.state = 3;
            goto s2;
        case 3:
            goto s3;
    }

s0:
    f.a = f.b = 1;
    return f.a;
s1:
    return f.b;
s2:
    while(true)
    {
        f.c = f.a + f.b;
        return f.c;
    s3:
        f.a = f.b;
        f.b = f.c;
    }
}

int main(int argc, char ** argv)
{
    using std::cout, std::endl;

    fib_frame f;
    for(int i = 0; i < 10; i++)
    {
        int x = co_fib(f);
        cout << x << endl;
    }

    return 0;
}