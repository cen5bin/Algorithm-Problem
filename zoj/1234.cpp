#include <cstdio>
#include <cstring>

typedef long long LL;
int a[5010];
int dp[5010][1010];

int min(int a, int b)
{
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int k, n;
		scanf("%d%d", &k, &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[i][0] = 0;
		int ans = -1;
		for (int i = n - 2; i; i--)
		{
			for (int j = 0; j <= (n-i-2)/3 && j < k+8; j++)
			{
				if (dp[i+2][j] != -1)
					dp[i][j+1] = dp[i+2][j] + (a[i] - a[i+1]) * (a[i] - a[i+1]);
				dp[i][j+1] = min(dp[i][j+1], dp[i+1][j+1]);
			}
		}
		for (int i = 1; i <= n; i++)
			ans = min(ans, dp[i][k+8]);
		printf("%d\n", ans);
	}
	return 0;
}
