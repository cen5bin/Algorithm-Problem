#include <cstdio>
#include <cstring>
const int N = 12;
int dp[1<<N];
int c[N][N];
inline int MAX(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &c[i][j]);
		memset(dp, 0, sizeof(dp));
		//dp[0][0] = 0;
		int ans = 0;
		for (int i = 0; i < (1<<n); i++)
		for (int j = 0; j < n; j++)
		if (((1<<j)&i) == 0)
		{
			for (int k = 0; k < n; k++)
			if ((i&(1<<k)) == 0 && k != j)
			{
				dp[i|(1<<j)] = MAX(dp[i|(1<<j)], dp[i] + c[k][j]);
				ans = MAX(dp[i|(1<<j)], ans);
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}
