#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#define EXPR(x) x

#define errif(cond, expr) \
    do                    \
    {                     \
        if (cond)         \
        {                 \
            expr;         \
        }                 \
    } while (0)

int main(int argc, char ** argv)
{
    EXPR(int a = 0);

    printf("a = %d\n", a);

    errif(a == 0, FATAL("a == 0", 0));
    errif(a == 0, WARN("a == 0"));
    errif(a == 0, INFO("a == 0"));
    errif(a == 0, NORM("a == 0"));

    return 0;
}