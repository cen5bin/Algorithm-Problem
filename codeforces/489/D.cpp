#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 3010;
vector<int> a[N];
int f[N];
void dfs(int x, int fa, int d)
{
	if (d == 2)
	{
		f[x] ++;
		return;
	}
	for (int i = 0; i < a[x].size(); i++)
	if (a[x][i] != fa)
	{
		dfs(a[x][i], x, d+1);
	}
}
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; i++) a[i].clear();
		for (int i = 0; i < m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			memset(f, 0, sizeof(f));
			dfs(i, i, 0);
			f[i] = 0;
			for (int j = 1; j <= n; j++)
			if (f[j] >= 2) ans += (f[j] - 1) * f[j] / 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
