#include <cstdio>
#include <cstring>

const int N = 310;
const int M = 35;
int a[N];
int cost[N][N];
int sum[N];
int dp[N][M];
int MIN(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	int n, m;
	sum[0] = 0;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)
			sum[i] = sum[i-1] + a[i];
		for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
		cost[i][j] = a[(i+j)/2] * ((i+j)/2-i+1) - (sum[(i+j)/2]-sum[i-1]) +
					(sum[j] - sum[(i+j)/2-1] - a[(i+j)/2] * (j - (i+j)/2 + 1));
		for (int i = 1; i <= n; i++)
			dp[i][1] = cost[1][i];
		for (int j = 2; j <= m; j++)
		for (int i = j; i <= n; i++)
		{
			dp[i][j] = 0x7fffffff;
			for (int k = j - 1; k < i; k++)
			dp[i][j] = MIN(dp[i][j], dp[k][j-1] + cost[k+1][i]);
		}
		printf("%d\n", dp[n][m]);
	}
	return 0;
}
