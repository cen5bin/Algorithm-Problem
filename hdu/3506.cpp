#include <cstdio>
#include <cstring>

const int N = 1010<<1;
int a[N], sum[N], dp[N][N], cost[N][N], s[N][N];

int MIN(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = n + 1; i <= 2 * n; i++) a[i] = a[i-n];
        sum[0] = 1;
        for (int i = 1; i <= 2 * n; i++) sum[i] = sum[i-1] + a[i];
        for (int i = 1; i <= 2 * n; i++)
        for (int j = i; j <= i + n - 1 && j <= 2 * n; j++)
            cost[i][j] = sum[j] - sum[i-1];
        for (int i = 1; i <= 2 * n; i++) s[i][i] = i, dp[i][i] = 0;
        for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n * 2; i++)
        {
            int j = l + i - 1;
            if (j > 2 * n) break;
            dp[i][j] = 0x7fffffff;
            for (int k = s[i][j-1]; k < j && k <= s[i+1][j]; k++)
            if (dp[i][j] >= dp[i][k] + dp[k+1][j] + cost[i][j])
            {
                dp[i][j] = dp[i][k] + dp[k+1][j] + cost[i][j];
                s[i][j] = k;
            }
        }
        int ans = dp[1][n];
        for (int i = 1; i <= n; i++) ans = MIN(ans, dp[i][i+n-1]);
        printf("%d\n", ans);
    }
    return 0;
}