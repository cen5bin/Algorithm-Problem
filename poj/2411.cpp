#include <cstdio>
#include <cstring>

long long dp[15][1<<12];

int valid[1<<12];
bool f[1<<12];
int cnt;
void dfs(int x, int y, int index, int n)
{
	if (index == n)
	{
		if (f[y]) return;
		f[y] = 1;
		valid[cnt++] = y;
		return;
	}
	int s1 = (x & (1<<index)) ? 1 : 0;
	int s2 = (x & (1<<index+1))?1 : 0;
	if (s1 == 0)
		return dfs(x, (1<<index)|y, index+1, n);
	dfs(x, y, index+1, n);
	if (s2)
		dfs(x, (3<<index)|y, index+2, n);
}

int main()
{
	int w, h;
	while (scanf("%d%d", &w, &h) && (w+h))
	{
		if (w*h%2)
		{
			puts("0");
			continue;
		}
		if (w > h)
		{
			w = w ^ h;
			h = w ^ h;
			w = w ^ h;
		}
		memset(dp, 0, sizeof(dp));
		memset(f, 0, sizeof(f));
		cnt = 0;
		dfs((1<<w)-1, 0, 0, w);
		for (int i = 0; i < cnt; i++)
			dp[0][valid[i]] = 1;
		for (int i = 0; i < h - 1; i++)
		{
			for (int j = 0; j < (1<<w); j++)
				if (dp[i][j])
				{
					cnt = 0;
					memset(f, 0, sizeof(f));
					dfs(j, 0, 0, w);
					for (int k = 0; k < cnt; k++)
							dp[i+1][valid[k]] += dp[i][j];
				}
		}
		printf("%lld\n", dp[h-1][(1<<w)-1]);
	}
	return 0;
}
