#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define inf 0xffff

vector <int> a[110];
int dp[110][3];

int min(int a,int b)
{
	return a < b ? a : b;
}


void dfs(int x, int fa)
{
	int size = a[x].size();
	if (size == 1 && a[x][0] == fa)
	{
		dp[x][0] = dp[x][2] = inf;
		return;
	}
	for (int i = 0; i < size; i++) 
	if (a[x][i] != fa)
	{
		dfs(a[x][i], x);
		dp[x][1] += dp[a[x][i]][0];
	}
	dp[x][2] = inf;
	dp[x][0] = inf;
	for (int i = 0; i < size; i++)
	if (a[x][i] != fa)
	{
		dp[x][2] = min(dp[x][2], dp[x][1] - dp[a[x][i]][0] + min(dp[a[x][i]][1], dp[a[x][i]][2]));
		dp[x][0] = min(dp[x][0], dp[x][1] - dp[a[x][i]][0] + dp[a[x][i]][2] + 1);
	}
	for (int i = 0; i < size - 1; i++)
	if (a[x][i]!=fa)
	{
		for (int j = i + 1; j < size; j++)
		if (a[x][j]!=fa)
		{
			dp[x][0] = min(dp[x][0], dp[x][1] - dp[a[x][i]][0] - dp[a[x][j]][0] + min(dp[a[x][i]][1], dp[a[x][i]][2]) + min(dp[a[x][j]][1], dp[a[x][j]][2])+1);
		}
	}
	if (dp[x][1] > inf) dp[x][1] = inf;
	if (dp[x][2] > inf) dp[x][2] = inf;
	if (dp[x][0] > inf) dp[x][0] = inf;
}


int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int x,y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		memset(dp, 0, sizeof(dp));
		dfs(1, 0);
		for (int i = 1; i <= n; i++)
		{
//			printf("%d %d %d %d\n", i, dp[i][0], dp[i][1], dp[i][2]);
		}


		if (dp[1][0] != inf)
		printf("%d\n", dp[1][0]);
		else puts("-1");
		for (int i = 1; i <= n; i++)
			a[i].clear();
	}
	return 0;
}
