#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 110;
int d[N], sum[N];
int dp[N][N];
#define inf 0x7fffffff
int main()
{
    int T;
    scanf("%d", &T);
    memset(dp, 0, sizeof(dp));
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);
        //memset(sum, 0, sizeof(sum));
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + d[i];
        for (int i = 1; i <= n; ++i) dp[i][i] = 0;
        for (int j = 2; j <= n; ++j)
        for (int i = 1; i <= n; ++i)
        if (i + j - 1<= n)
        {
            int end = i + j - 1;
            dp[i][end] = inf;
            for (int k = i; k <= end; ++k)
                dp[i][end] = min(dp[i][end], dp[i][k-1] + dp[k+1][end] + (sum[end]-sum[k])* (k-i) +d[k] * (j-1));
        }
        static int cas = 1;
        printf("Case #%d: %d\n", cas++, dp[1][n]);
    }
    return 0;
}
