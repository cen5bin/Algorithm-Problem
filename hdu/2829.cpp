#include <cstdio>
#include <cstring>

const int N = 1010;
int a[N];
int dp[N][N], cost[N][N], s[N][N];
int sum[N];
int MIN(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) && n + m)
	{
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		sum[0] = 0;
		for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i];
		for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
		if (i == j) cost[i][j] = 0;
		else cost[i][j] = cost[i][j-1] + (sum[j-1]-sum[i-1]) * a[j];
		
		for (int i = 1; i <= n; i++) dp[i][0] = cost[1][i], s[i][i] = i;
		for (int j = 1; j <= m; j++)
		for (int i = j + 1; i <= n; i++)
		{
			dp[i][j] = 0x7fffffff;
			for (int k = s[i-1][j]; k < i; k++)
			if (dp[i][j] >= dp[k][j-1] + cost[k+1][i])
			{
				dp[i][j] = dp[k][j-1] + cost[k+1][i];
				s[i][j] = k;
			}
		}
		printf("%d\n", dp[n][m]);
	}
	return 0;
}
