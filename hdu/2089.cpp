#include <cstdio>
#include <cstring>
int dp[10][10];
void init()
{
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < 8; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                if ((k!=2 || j!=6) && j != 4)
                dp[i][j] += dp[i-1][k];
    return;
    for (int i = 1; i < 8; ++i)
    {
        for (int j = 0; j < 10; ++j)
            printf("%d ", dp[i][j]);
        puts("");
    }
}

int solve(int n)
{
    int digit[10];
    int len = 0;
    memset(digit, 0, sizeof(digit));
    while (n)
    {
        digit[++len] = n % 10;
        n /= 10;
    }
    int ans = 0;
    for (int i = len; i > 0; --i)
    {
    //    printf("%d ", digit[i]);
        for (int j = digit[i]-1; j >= 0; --j)
        if (j!=2||digit[i+1]!=6) ans+= dp[i][j];
        if (digit[i] == 4 || (digit[i] == 2 && digit[i+1] == 6)) break;
    }
  //  puts("");
    return ans;
}

int main()
{
    init();
    int n, m;
    while (scanf("%d%d", &n, &m) && (n+m))
    {
        //printf("%d %d\n", solve(m+1), solve(n));
        printf("%d\n", solve(m+1) - solve(n));
    }
    return 0;
}
