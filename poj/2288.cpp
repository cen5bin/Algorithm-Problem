#include <cstdio>
#include <cstring>

typedef long long LL;
LL a[15];
int c[15][15];
LL dp[1<<14][15][15];
LL path[1<<14][15][15];


bool judge(int x,int y,int z)
{
	return c[x][y] && c[x][z] && c[y][z];
}

LL max(LL a, LL b)
{
	return a  > b ? a : b;
}

void solve(int n)
{
	memset(path, 0, sizeof(path));
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	if (i != j && c[i][j])
	{
		dp[(1<<i)|(1<<j)][i][j] = a[i] + a[j] + a[i] * a[j];
		path[(1<<i)|(1<<j)][i][j] = 1;
	}
	for (int i = 0; i < (1<<n); i++)
	for (int j = 0; j < n; j++)
	if ((i&(1<<j)) == 0)
	{
		for (int k = 0; k < n; k++)
		if (k != j && (i&(1<<k)) && c[j][k])
		{
			for (int l = 0; l < n; l++)
			if (l!=k && (i&(1<<l)) && l!=j && c[l][k] && dp[i][l][k]!=-1)
			{
				LL tmp = dp[i][l][k] + a[j] + a[j] * a[k] + (judge(l, k, j)?a[l]*a[k]*a[j]:0);
				if (dp[i|(1<<j)][k][j] < tmp)
				{
					dp[i|(1<<j)][k][j] = tmp;
					path[i|(1<<j)][k][j] = path[i][l][k];
				}
				else if (dp[i|(1<<j)][k][j] == tmp)
					path[i|(1<<j)][k][j] += path[i][l][k];
			}
		}
	}

}


int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n,m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		if (n==1)
		{
			printf("%lld %d\n", a[0], 1);
			continue;
		}
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x--;
			y--;
			c[x][y] = c[y][x] = 1;
		}
		solve(n);
		LL max0 = -1;
		LL path0 = 0;
		int all = (1<<n)-1;
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		if (i != j && dp[all][i][j]!=-1)
		{
			//printf("%lld\n", dp[all][i][j]);
			if (dp[all][i][j] > max0)
			{
				max0 = dp[all][i][j];
				path0 = path[all][i][j];
			}
			else if (dp[all][i][j] == max0)
				path0+=path[all][i][j];
		}
		if (max0 == -1)
			printf("0 0\n");
		else
		printf("%lld %lld\n", max0, path0 / 2);
	}
	return 0;
}

