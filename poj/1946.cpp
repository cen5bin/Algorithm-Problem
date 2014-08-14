#include <cstdio>
#include <cstring>

int dp[25][210][110];

int min(int a, int b)
{
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;		
}

int main()
{
	int n, e, d;
	while (scanf("%d%d%d", &n, &e, &d) == 3)
	{
		memset(dp, -1, sizeof(dp));
		int ans = -1;
		dp[0][0][e] = 0;
		for (int i = 0; i < n; i++)
		for (int j = 0; j <= d; j++)
		for (int k = e - j; k >= 0; k--)
		if (dp[i][j][k] != -1)
		{
			dp[i+1][j][e-j] = min(dp[i+1][j][e-j], dp[i][j][k]);
			for (int t = 1; t * t <= k; t++)
			{
				dp[i][j+t][k-t*t] = min(dp[i][j+t][k-t*t], dp[i][j][k]+1);
				if (j+t >= d)
					ans = min(ans, dp[i][j+t][k-t*t]);
			}
		}
		if (ans == -1) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}
