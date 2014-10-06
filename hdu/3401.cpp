#include <cstdio>
#include <cstring>

template <class T>
T MAX(T a, T b)
{
	return a > b ? a : b;
}

const int N = 2010;
int dp[N][N], AP[N], BP[N], AS[N], BS[N];
struct point
{
	int v, id;
}q[N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m, w;
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d%d", &AP[i], &BP[i], &AS[i], &BS[i]);
		for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = -0xfffffff;
		for (int i = 1; i <= w+1; i++)
		for (int j = 0; j <= AS[i] && j <= m; j++)
			dp[i][j] = MAX(- AP[i] * j, dp[i-1][j]);
		dp[0][0] = 0;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
				dp[i][j] = MAX(dp[i-1][j], dp[i][j]);
			if (i <= w+1) continue;
			int hh = 0, tt = 0;
			for (int j = 0; j <= m; j++)
			{
				int tmp = dp[i-w-1][j] + AP[i] * j;
				while (hh < tt && q[tt-1].v <= tmp) tt--;
				q[tt].v = tmp, q[tt++].id = j;
				while (hh < tt && q[hh].id < j - AS[i]) hh++;
				dp[i][j] = MAX(dp[i][j], q[hh].v - AP[i] * j);
			}
			hh = tt = 0;
			for (int j = m; j >= 0; j--)
			{
				int tmp = dp[i-w-1][j] + BP[i] * j;
				while (hh < tt && q[tt-1].v <= tmp) tt--;
				q[tt].v = tmp, q[tt++].id = j;
				while (hh < tt && q[hh].id > j + BS[i]) hh++;
				dp[i][j] = MAX(dp[i][j], q[hh].v - BP[i] * j);
			}
		}
		int ans = 0;
		for (int i = 0; i <= m; i++) ans = MAX(ans, dp[n][i]);
		printf("%d\n", ans);
	}
	return 0;
}
