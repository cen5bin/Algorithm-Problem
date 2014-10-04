#include <cstdio>
#include <cstring>
const int N = 11;
typedef long long LL;
LL c[N][N];
LL dp[60000][N];
int kk[60000][12], tt[60000];
LL MIN(LL a, LL b)
{
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}
int main()
{
	int n, m;
	int aa[12];
	aa[0] = 1;
	memset(kk, 0, sizeof(kk));
	memset(tt, 0, sizeof(tt));
	for (int i = 0; i < 60000; i++)
	{
		int tmp = i;
		for (int j = 0; tmp && j < 12; j++) 
		{
			kk[i][j] = tmp % 3,  tmp /= 3;
			tt[i]+=(kk[i][j])?1:0;
		}
	}
	for (int i = 1; i < 12; i++) aa[i] = 3 * aa[i - 1]; 
	while (scanf("%d%d", &n, &m) == 2)
	{
		memset(c, -1, sizeof(c));
		for (int i = 0; i < m; i++)
		{
			int x, y;
			LL z;
			scanf("%d%d%lld", &x, &y, &z);
			x--;
			y--;
			if (c[x][y] == -1 || c[x][y] > z) c[x][y] = c[y][x] = z;
		}
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < n; i++) dp[aa[i]][i] = 0;
		for (int i = 0; i < aa[n]; i++)
		for (int j = 0; j < n; j++)
		if (dp[i][j] != -1)
		{
			for (int k = 0; k < n; k++)
			if (c[k][j] != -1 && kk[i][k] < 2)
				dp[i+aa[k]][k] = MIN(dp[i+aa[k]][k], dp[i][j] + c[k][j]);
		}
		LL ans = -1;
		for (int i = 0; i < n; i++) //ans = MIN(ans, dp[(1<<n)-1][i]);
		for (int j = 0; j < aa[n]; j++)
		if (tt[j] == n) ans = MIN(ans, dp[j][i]);
		printf("%lld\n", ans);
	}
	return 0;
}
