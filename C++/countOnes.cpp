#include <stdio.h>
#include <stdlib.h>
#include <typeinfo.h>

#define POW(c) (1 << (c))

#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))

#define ROUND(n, c) (((n)&MASK(c)) + ((n) >> POW(c) & MASK(c)))

int countOnes2(unsigned int n)
{
    n = ROUND(n, 0);
    n = ROUND(n, 1);
    n = ROUND(n, 2);
    n = ROUND(n, 3);
    n = ROUND(n, 4);
    return n;
}

int main(int argc, char const *argv[])
{
    printf("%d\n", countOnes2(10256));
    system("pause");
    return 0;
}