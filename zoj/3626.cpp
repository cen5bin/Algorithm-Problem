#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
struct edge
{
	int v, c;
	edge(){}
	edge(int _v, int _c):v(_v), c(_c){}
};
const int N = 110;
const int M = 210;
vector<edge> a[N];
int dp[N][M];
int f[N];
int m;
int MAX(int a, int b)
{
	return a > b ? a : b;
}

void dfs(int x, int fa)
{
	int size = a[x].size();
	for (int i = 0; i <= m; i++) dp[x][i] = -1;
	dp[x][0] = f[x];
	for (int i = 0; i < size; i++)
	{
		int v = a[x][i].v;
		if (v == fa) continue;
		dfs(v, x);
		int c = a[x][i].c;
		for (int j = m; j >= 2*c; j--)
		for (int k = 0; k <= j-2*c; k++)
		if (dp[x][j-2*c-k] != -1 && dp[v][k] != -1)
			dp[x][j] = MAX(dp[x][j], dp[x][j-2*c-k]+dp[v][k]);
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++) scanf("%d", &f[i]);
		for (int i = 1; i < n; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			a[x].push_back(edge(y, z));
			a[y].push_back(edge(x, z));
		}
		int k;
		scanf("%d%d", &k, &m);
		dfs(k, k);
		int ans = 0;
		for (int i = 0; i <= m; i++) ans = MAX(ans, dp[k][i]);
		printf("%d\n", ans);
		for (int i = 1; i <= n; i++) a[i].clear();
	}
	return 0;
}
