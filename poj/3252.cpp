#include <cstdio>
#include <cstring>

int dp[35][2][70];
void init()
{
    memset(dp, 0, sizeof(dp));
    dp[0][0][32] = 1;
    for (int i = 1; i < 32; ++i)
    for (int j = 0; j < 2; ++j)
    for (int j1 = 0; j1 < 2; ++j1)
    for (int k = 32 - i; k <= 32+i; ++k)
    {
        dp[i][j][k] += dp[i-1][j1][k-(1-j*2)];
    }
    return;
    for (int i = 1; i < 5; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 32-i; k <= 32+i; ++k)
                printf("(%d, %d, %d) %d\n", i, j, k-32, dp[i][j][k]);
}

int solve(int n)
{
    int digit[35];
    memset(digit, 0, sizeof(digit));
    int len = 0;
    while (n)
    {
        digit[++len] = n & 1;
        n >>= 1;
    }
    int ans = 0;
    int cnt = -1;
    for (int i = len - 1; i; --i)
    {
        for (int j = 0; j < digit[i]; ++j)
            for (int k = 32-cnt; k <= 32+i; ++k)
                ans += dp[i][j][k];
        cnt += 1 - digit[i]*2;
    }
    for (int j = len - 1; j; --j)
    for (int i = 32; i < 70; ++i) ans += dp[j][1][i];
    return ans;
}

int main()
{
    init();
       // for (int i = 1; i <= 20; ++i)
       // printf("%d %d\n", i, solve(i + 1));
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        printf("%d\n", solve(m+1) - solve(n));
    }
    return 0;
}
