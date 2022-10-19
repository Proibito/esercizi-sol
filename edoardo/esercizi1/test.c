#include <stdio.h>

int main()
{
    union
    {
        int n;
        char c;
        double f;
    } d;
    d.c = 'W';
    d.n = 0xa300 | 'k';
    // var_du
    printf("%c\n", d.c);
}