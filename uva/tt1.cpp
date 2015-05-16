#include <cstdio>
#include <cstring>

typedef long long LL;
const int N = 1010;
struct point
{
    LL x, w;
}p[N];

LL w[N][N], dp[N][N], sum1[N], sum2[N];
int ss[N][N];

int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k) == 2)
    {
        for (int i = 1; i <= n; ++i) scanf("%lld%lld", &p[i].x, &p[i].w);
        sum1[0] = sum2[0] = 0;
        for (int i = 1; i <= n; ++i) 
        {
            sum1[i] = sum1[i-1] + p[i].w;
            sum2[i] = sum2[i-1] + p[i].x * p[i].w;
        }
        for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            w[i][j] = (sum1[j]-sum1[i-1]) * p[j].x - (sum2[j]-sum2[i-1]);
        for (int i = 1; i <= n; ++i) dp[i][1] = w[1][i], ss[i][1] = 1;
        for (int i = 1; i <= k; ++i) ss[n+1][i] = n;

        for (int j = 2; j <= k; ++j)
        for (int i = n; i >= j; --i)
        {
            dp[i][j] = -1;
            for (int t = ss[i][j-1]; t <= ss[i+1][j]; ++t)
                if (dp[i][j] == -1 || dp[i][j] > dp[t][j-1] + w[t+1][i])
                {
                    ss[i][j] = t;
                    dp[i][j] = dp[t][j-1] + w[t+1][i];
                }
        }
        printf("%lld\n", dp[n][k]);
    }
    return 0;
}
