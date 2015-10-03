#include <cstdio>
#include <cstring>
typedef unsigned long long LL;
const LL M = 1000000007;
LL count[20][10][7][7];
LL sum[20][10][7][7];
LL sum2[20][10][7][7];

void init()
{
    memset(count, 0, sizeof(count));
    memset(sum, 0, sizeof(sum));
    memset(sum2, 0, sizeof(sum2));
    count[0][0][0][0] = 1;
    LL yu = 1, yu1 = 1;
    for (int i = 1; i <= 19; ++i, yu = yu*10%M, yu1 = yu1 * 10 % 7)
    for (int j = 0; j < 10; ++j)
    if (j != 7)
    {
        for (int k = 0; k < 7; ++k)
        for (int t = 0; t < 7; ++t)
        {
            for (int j1 = 0; j1 < 10; ++j1)
            if (j1 != 7)
            {
                int k1 = (k - j * yu1 % 7 + 7) % 7;
                int t1 = (t - j % 7 + 7) % 7;
                count[i][j][k][t] += count[i-1][j1][k1][t1];
                count[i][j][k][t] %= M;
                sum[i][j][k][t] += count[i-1][j1][k1][t1] * yu % M * j % M + sum[i-1][j1][k1][t1];
                sum[i][j][k][t] %= M;
                sum2[i][j][k][t] += count[i-1][j1][k1][t1]*yu % M *yu % M * j * j % M + yu*sum[i-1][j1][k1][t1] % M * 2 * j % M+ sum2[i-1][j1][k1][t1];
                sum2[i][j][k][t] %= M;
            }
        }
    }
    return;
    for (int i = 1; i < 3; ++i)
    for (int j = 0; j < 10; ++j)
    for (int k = 0; k < 7; ++k)
    for (int t = 0; t < 7; ++t)
        if (sum2[i][j][k][t]) 
            printf("(%d, %d, %d, %d) %lld\n", i, j, k, t, sum2[i][j][k][t]);
}

LL solve(LL n)
{
    LL digit[20];
    memset(digit, 0, sizeof(digit));
    int len = 0;
    LL yu = 1;
    while (n)
    {
        digit[++len] = n % 10;
        n /= 10;
        if (n == 0) break;
        yu = yu * 10;
    }
    LL ans = 0;
    LL now1 = 0, now2 = 0;
    LL pre = 0;
    for (int i = len; i; --i)
    {
        for (int j = 0; j < digit[i]; ++j)
        if (j != 7)
        {
            for (int k = 0; k < 7; ++k)
            if ((k+now1)%7!=0)
            {
                for (int t = 0; t < 7; ++t)
                    if ((t+now2)%7!=0)
                        ans += sum2[i][j][k][t] + pre * pre % M * count[i][j][k][t] % M +  sum[i][j][k][t] * pre % M * 2;
                ans %= M;
            }
        }
        if (digit[i] == 7) break;
        pre = (pre + yu % M * digit[i]) % M;
        now1 = (now1 + yu % 7 * digit[i]) % 7;
        now2 = (now2 + digit[i]) % 7;
        yu /= 10;
    }
    return ans;
}


int main()
{
    init();
    //for (int i = 100000000; i <= 100000010; ++i) printf("%d %llu\n", i, solve(i+1));
    int T;
    scanf("%d", &T);
    while (T--)
    {
        LL x, y;
        scanf("%llu%llu", &x, &y);
        //printf("%llu %llu\n", solve(x+1), solve(y+1));
        printf("%llu\n", (solve(y+1) + M - solve(x)) % M);
    }
    return 0;
}
