// 最长公共子序列长度 递归版和迭代版
// 最长公共子序列内容
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define FROM_UP 0
#define FROM_LEFT 1
#define FROM_UP_AND_LEFT 2

int LCS1(string x, string y)
{
    // 长度-递归版
    int i = x.size();
    int j = y.size();
    if (i == 0 || j == 0)
        return 0;
    if (x[i - 1] == y[j - 1])
        return 1 + LCS1(x.substr(0, i - 1), y.substr(0, j - 1));
    else
        return max(LCS1(x.substr(0, i - 1), y.substr(0, j)), LCS1(x.substr(0, i), y.substr(0, j - 1)));
}

int LCS2(string x, string y)
{
    // 长度-迭代版
    int len1 = x.size();
    int len2 = y.size();
    vector<vector<int>> c(len1 + 1, vector<int>(len2 + 1, 0));
    vector<vector<int>> d(len1, vector<int>(len2, 0));
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                d[i - 1][j - 1] = FROM_UP_AND_LEFT;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                d[i - 1][j - 1] = FROM_UP;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                d[i - 1][j - 1] = FROM_LEFT;
            }
        }
    }
    return c[len1][len2];
}

string GetLCS(string x, string y)
{
    //内容-只求了一个
    string value = "";
    int len1 = x.size();
    int len2 = y.size();
    vector<vector<int>> c(len1 + 1, vector<int>(len2 + 1, 0));
    vector<vector<int>> d(len1, vector<int>(len2, 0));
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                d[i - 1][j - 1] = FROM_UP_AND_LEFT;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                d[i - 1][j - 1] = FROM_UP;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                d[i - 1][j - 1] = FROM_LEFT;
            }
        }
    }

    int i = len1 - 1, j = len2 - 1;
    while (true)
    {
        if (d[i][j] == FROM_UP)
            j--;
        else if (d[i][j] == FROM_LEFT)
            i--;
        else
        {
            i--;
            j--;
            value += x[i];
        }
        if (i < 0 || j < 0)
            break;
    }
    reverse(value.begin(), value.end());
    return value;
}

// TODO: 求解全部最长公共子序列

int main(int argc, char const *argv[])
{
    string a = "aabcd";
    string b = "12abcabcd";
    //printf("1: The longest common subsequence length of %s and %s is %d\n", a.c_str(), b.c_str(), LCS1(a, b));
    //printf("2: The longest common subsequence length of %s and %s is %d\n", a.c_str(), b.c_str(), LCS2(a, b));
    printf("3: The longest common subsequence of %s and %s is %s\n", a.c_str(), b.c_str(), GetLCS(a, b).c_str());
    system("pause");
    return 0;
}
