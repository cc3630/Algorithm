#include <stdio.h>
#include <stdlib.h>
using namespace std;

int fibonacci_1(int n)
{
    if (n < 3)
        return 1;
    return fibonacci_1(n - 1) + fibonacci_1(n - 2);
}

int fibonacci_2(int n)
{
    int f = 1, g = 1;
    if (n < 3)
        return 1;
    while (n >= 3)
    {
        g = f + g;
        f = g - f;
        n--;
    }
    return g;
}

int main(int argc, char const *argv[])
{
    int n = 11;
    printf("斐波那契数列第%d项的值是%d\n", n, fibonacci_1(n));
    printf("斐波那契数列第%d项的值是%d\n", n, fibonacci_2(n));
    system("pause");
    return 0;
}
