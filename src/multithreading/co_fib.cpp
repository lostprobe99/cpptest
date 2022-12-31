#include <iostream>
#include <exception>

struct fib_frame
{
    int state = 0;
    int a, b, c;
    std::exception_ptr exception;

    int resume()
    {
        try
        {
            switch (state)
            {
            case 0:
                state = 1;
                goto s0;
            case 1:
                state = 2;
                goto s1;
            case 2:
                state = 3;
                goto s2;
            case 3:
                goto s3;
            }

        s0:
            a = b = 1;
            return a;
        s1:
            return b;
        s2:
            while (true)
            {
                c = a + b;
                return c;
            s3:
                a = b;
                b = c;
            }
        }
        catch (...)
        {
            this->exception = std::current_exception();
        }
    }
};

int main(int argc, char **argv)
{
    using std::cout, std::endl;

    fib_frame fib;
    for (int i = 0; i < 10; i++)
    {
        int x = fib.resume();
        if(fib.exception)
        {
        }
        cout << x << endl;
    }

    return 0;
}