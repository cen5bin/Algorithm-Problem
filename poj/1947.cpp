#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define inf 0xffff

int n, p;
vector<int>a[155];
int ans;
int dp[155][155];


int min(int a, int b)
{
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

void dfs(int x, int fa)
{
	int size = a[x].size();
	if (size == 1 && a[x][0] == fa) {
	int tmp = dp[x][p];
	if (fa != 0 && dp[x][p]!=-1) tmp++;
	ans = min(ans, tmp);
		return;
	}
	for (int i = 0; i < size; i++)
	if (a[x][i] != fa)
	{
		dfs(a[x][i], x);
		for (int j = p; j; j--)
		{
			if (dp[x][j] != -1) dp[x][j] = dp[x][j] + 1;
			for (int k = 1; k < j; k++)
				if (dp[x][j-k]!=-1&&dp[a[x][i]][k]!=-1)
				dp[x][j] = min(dp[x][j], dp[x][j-k]+dp[a[x][i]][k]);
		}
	}
	int tmp = dp[x][p];
	if (fa != 0 && dp[x][p]!=-1) tmp++;
	ans = min(ans, tmp);
}

int main()
{
	while (scanf("%d%d", &n, &p) == 2)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		ans = inf;
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[i][1] = 0;
		dfs(1, 0);
		printf("%d\n", ans);
		for (int i = 1; i <= n; i++)
			a[i].clear();
	}
	return 0;
}
