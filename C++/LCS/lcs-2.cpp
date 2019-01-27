// 获取全部最长公共子序列
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

#define FROM_UP_AND_LEFT 0
#define FROM_UP 1
#define FROM_LEFT 2
#define FROM_UP_OR_LEFT 3

const int MAXN = 100;
const int mod = 1e8;
int n, m;
int f[MAXN][MAXN] = {0}, g[MAXN][MAXN] = {0};

void print_lcs(char *s, int g[MAXN][MAXN], int i, int j)
{
    if (!i || !j)
        return;
    switch (g[i][j])
    {
    case FROM_UP_AND_LEFT:
        print_lcs(s, g, i - 1, j - 1);
        cout << s[i];
        break;
    case FROM_UP:
        print_lcs(s, g, i - 1, j);
        break;
    case FROM_LEFT:
        print_lcs(s, g, i, j - 1);
        break;
    case FROM_UP_OR_LEFT:
        cout << '(';
        print_lcs(s, g, i - 1, j);
        cout << '+';
        print_lcs(s, g, i, j - 1);
        cout << ')';
        break;
    }
}

int main()
{
    char S[MAXN] = "0ABCD", T[MAXN] = "0ACBD";
    n = strlen(S + 1);
    m = strlen(T + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (S[i] == T[j])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
                g[i][j] = FROM_UP_AND_LEFT;
            }
            else
            {
                if (f[i - 1][j] > f[i][j - 1])
                    g[i][j] = FROM_UP;
                else if (f[i - 1][j] < f[i][j - 1])
                    g[i][j] = FROM_LEFT;
                else
                    g[i][j] = FROM_UP_OR_LEFT;
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    print_lcs(S, g, n, m);
    system("pause");
}