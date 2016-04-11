#include <cstdio>
#include <cstring>
#define max(a, b)  (((a) > (b))? (a) : (b))
typedef long long LL;

const int N = 5010;
LL dp[N][2];
LL sum[N];
LL a[N];

int main()
{
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) == 3)
	{
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; i++) sum[i] += sum[i-1] + a[i];
		memset(dp, 0, sizeof(dp));
		LL ans = 0;
		int now = 0;
		for (int i = 1; i <= k; i++)
		{
			now = 1 - now;
			for (int j = m; j <= n; j++)
			{
				dp[j][now] = max(dp[j-1][now], dp[j-m][1-now]+sum[j]-sum[j-m]);
				ans = max(ans, dp[j][now]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
