#include<stdio.h>

int main()
{
    unsigned char a=10, b=30, c=2, res;
    res = a*b;
    printf("a*b => res, evaluated as %d*%d => %d\n", a, b, res);
    res = a*b/c;            //integer promotion
    printf("a*b/c => res, evaluated as %d*%d/%d => %d\n", a, b, c, res);

    return 0;
}