#include <cstdio>
#include <cstring>
typedef unsigned long long LL;
int digit[30];
LL dp[30][10];
void init()
{
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < 19; ++i)
    for (int j = 0; j < 10; ++j)
    for (int k = 0; k < 10; ++k)
    {
        if (k != 9 || j != 4)
        dp[i][j] += dp[i-1][k];
    }
}

LL solve(LL n)
{
    int digit[30];
    memset(digit, 0, sizeof(digit));
    LL ans = n;
    int len = 0;
    while (n)
    {
        digit[++len] = n % 10;
        n /= 10;
    }
    for (int i = len; i; --i)
    {
        for (int j = 0; j < digit[i]; ++j)
        if (j != 9 || digit[i] != 4) ans-=dp[i][j];
        if (digit[i] == 9 && digit[i+1] == 4) break;
    }
    return ans;
}


int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        LL n;
        scanf("%llu", &n);
        printf("%llu\n", solve(n+1));
    }
    return 0;
}
