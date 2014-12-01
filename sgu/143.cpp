#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 16010;
vector<int> a[N];
int dp[N];
int ans;


void dfs(int x, int fa)
{
	for (int i = 0; i < a[x].size(); i++)
	{
		int v = a[x][i];
		if (v == fa) continue;
		dfs(v, x);
		if (dp[v] > 0) dp[x] += dp[v];
	}
	ans = max(ans, dp[x]);
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++) 
		{
			scanf("%d", &dp[i]);
			a[i].clear();
		}
		for (int i = 1; i < n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		ans = -1001;
		dfs(1, 1);
		printf("%d\n", ans);
		return 0;
	}
	return 0;
}
