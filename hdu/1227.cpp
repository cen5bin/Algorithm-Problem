#include <cstdio>
#include <cstring>
const int N = 210;
const int M = 35;
int cost[N][N];
int dp[N][M];
int a[N];
int MIN(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	int n, m;
	for (int i = 0; i < N; i++) dp[i][i] = 0;
	int cas = 0;
	while (scanf("%d%d", &n, &m) && m + n)
	{
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		cost[i][j] = cost[i][j-1] + a[j] - a[(i+j)/2];
		for (int i = 1; i <= n; i++) dp[i][1] = cost[1][i];
		for (int j = 2; j <= m; j++)
		for (int i = j; i <= n; i++)
		{
			dp[i][j] = 0x7fffffff;
			for (int k = j - 1; k < i; k++)
				dp[i][j] = MIN(dp[i][j], dp[k][j-1] + cost[k+1][i]);
		}
		printf("Chain %d\n", ++cas);
		printf("Total distance sum = %d\n\n", dp[n][m]);
	}
	return 0;
}
