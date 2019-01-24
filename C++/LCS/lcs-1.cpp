#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;
int a[5009] = {0};
int b[5009] = {0};
int c[5009] = {0};
int F[5009] = {0};
int tf[5009] = {0};
int S[5009] = {0};
int ts[5009] = {0};
int ca = 0, cb = 0;
int MOD = 100000000;
char temp;
int main()
{
    while (cin >> temp)
    {
        if (temp == '.')
            break;
        ca++;
        a[ca] = temp - 'A' + 1;
    }
    while (cin >> temp)
    {
        if (temp == '.')
            break;
        cb++;
        b[cb] = temp - 'A' + 1;
    }
    for (int i = 1; i <= ca; i++)
        ts[i] = 1;
    int nowF, nowS;
    for (int i = 1; i <= cb; i++)
    {
        for (int j = 1; j <= ca; j++)
        {
            if (a[j] == b[i])
            {
                nowF = tf[j - 1] + 1;
                nowS = ts[j - 1];
                if (tf[j - 1] == 0)
                    nowS = 1;
                if (nowF == F[j])
                {
                    S[j] += nowS;
                    S[j] %= MOD;
                }
                if (nowF > F[j])
                {
                    F[j] = nowF;
                    S[j] = nowS;
                    S[j] %= MOD;
                }
            }
        }
        for (int j = 1; j <= ca; j++)
        {
            tf[j] = F[j];
            ts[j] = S[j];
            if (tf[j - 1] == tf[j])
            {
                ts[j] += ts[j - 1];
                ts[j] %= MOD;
            }
            if (tf[j] == 0)
                ts[j] = 1;
            if (tf[j - 1] > tf[j])
            {
                tf[j] = tf[j - 1];
                ts[j] = ts[j - 1];
                ts[j] %= MOD;
            }
            if (tf[j] == 0)
                ts[j] = 1;
        }
    }
    cout << tf[ca] << endl
         << ts[ca] << endl;
    system("pause");
    return 0;
}