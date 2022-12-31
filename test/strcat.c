#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * concat(char *dst, char const *str1, char const *str2)
{
    char * p = dst;
    char * s1 = str1, *s2 = str2;
    while(*s1)
        *p++ = *s1++;
    while(*s2)
        *p++ = *s2++;
    *p = '\0';
    return dst;
}

int main(int argc, char ** argv)
{
    char s[128] = {0};
    concat(s, "hello", "world");
    printf("%s\n", s);

    printf("%s\n", concat(s, "hello", "world"));
    printf("%s\n", concat(s, "hello ", "world"));
    printf("%s\n", concat(s, "", ""));

    return 0;
}