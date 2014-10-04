#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 100010;
struct edge
{
	int v;
	LL c;
	edge(){}
	edge(int _v, LL _c):v(_v), c(_c){}
};
vector<edge> a[N];
LL dp[N][2];
bool f[N];
LL MIN(LL a, LL b)
{
	if (a == -1) return b;
	else if (b == -1) return a;
	else return a < b ? a : b;
}

void dfs(int x, int fa)
{
	int size = a[x].size();
	dp[x][0] = dp[x][1] = 0;
	for (int i = 0; i < size; i++)
	{
		int v = a[x][i].v;
		if (v == fa) continue;
		dfs(v, x);
		dp[x][f[x]] += MIN(dp[v][0], dp[v][1] + a[x][i].c);
	}
	if (f[x]) dp[x][0] = -1;
	else
	{
		dp[x][1] = dp[x][0];
		for (int i = 0; i < size; i++)
		{
			int v = a[x][i].v;
			if (v == fa) continue;
			dp[x][1] = MIN(dp[x][1], dp[x][0] - MIN(dp[v][0], dp[v][1]+a[x][i].c)+dp[v][1]);
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n - 1; i++)
		{
			int x, y;
			LL z;
			scanf("%d%d%lld", &x, &y, &z);
			a[x].push_back(edge(y, z));
			a[y].push_back(edge(x, z));
		}
		memset(f, 0, sizeof(f));
		for (int i = 0; i < k; i++) 
		{
			int x;
			scanf("%d", &x);
			f[x] = 1;
		}
		dfs(1, 1);
		printf("%lld\n", MIN(dp[1][0], dp[1][1]));
		for (int i = 0; i < n; i++) a[i].clear();
	}
	return 0;
}
