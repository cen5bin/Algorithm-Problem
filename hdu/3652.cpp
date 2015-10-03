#include <cstdio>
#include <cstring>

int dp[12][10][15];
void init()
{
    memset(dp, 0, sizeof(dp));
    int yu = 1;
    dp[0][0][0] = 1;
    for (int i = 1; i <= 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        for (int k = 0; k < 13; ++k)
        for (int j1 = 0; j1 < 10; ++j1)
        if (j1 != 3 || j != 1)
        {
           
            int k1 = (k - j * yu % 13 + 13) % 13;
            dp[i][j][k] += dp[i-1][j1][k1];
        }
        yu = yu * 10 % 13;
    }
    return;
    for (int i = 1; i < 3; ++i)
    {
        for (int j = 0; j < 10; ++j)
            printf("%d ", dp[i][j][0]);
        puts("");
    }
}

int solve(int n)
{
    int digit[12];
    memset(digit, 0, sizeof(digit));
    int len = 0;
    int ans = (n-1) / 13;
    int ll = 1;
    while (n)
    {
        digit[++len] = n % 10;
        n /= 10;
        ll *= 10;
    }
    ll /= 10;
    int yu = 0;
    for (int i = len; i; --i)
    {
        for (int j = 0; j < digit[i]; ++j)
        {
            if (j!=3 || digit[i+1] != 1)
            ans -= dp[i][j][(13-yu)%13];
        }
        if (digit[i] == 3 && digit[i+1] == 1) break;
        yu = (yu + ll * digit[i]) % 13;
        ll /= 10;
    }
    return ans + 1;
}


int main()
{
    init();
    int n;
    while (scanf("%d", &n) == 1)
    {
        printf("%d\n", solve(n+1));
    }
    return 0;
}
