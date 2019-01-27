// 获取最长公共子序列长度的个数
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int MAXN = 100;
const int mod = 1e8;
int n, m;
int f[MAXN][MAXN] = {0}, g[MAXN][MAXN] = {0};

int main()
{
    char S[MAXN] = "0ABCD", T[MAXN] = "0ACBD";
    n = strlen(S + 1);
    m = strlen(T + 1);
    for (int i = 0; i <= m; i++)
        g[0][i] = 1; //表示第一个序列长度为0时，只有1种LCS方案
    for (int i = 0; i <= n; i++)
        g[i][0] = 1; //表示第二个序列长度为0时，只有1种LCS方案
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (S[i] == T[j])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
                g[i][j] += g[i - 1][j - 1];
            }
            else
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (f[i][j] == f[i][j - 1])
                g[i][j] += g[i][j - 1];
            if (f[i][j] == f[i - 1][j])
                g[i][j] += g[i - 1][j];
            if (S[i] != T[j] && f[i][j] == f[i - 1][j - 1])
                // S[i]与T[j]不匹配时，f[i][j] == f[i - 1][j - 1]表示f[i][j]、f[i][j - 1]、f[i - 1][j]、f[i - 1][j - 1]均相同，此时S[i]和T[j]均未做出贡献，[i - 1][j - 1]->[i - 1][j]->[i][j]与[i - 1][j - 1]->[i][j-1]->[i][j]两个路径是重复的，因此舍去一个g[i - 1][j - 1]
                g[i][j] -= g[i - 1][j - 1];
        }
    }
    printf("%d\n%d", f[n][m], g[n][m]);
    system("pause");
}