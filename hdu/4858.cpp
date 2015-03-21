#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int N = 100010;
vector<int> a[N];
vector<int> heavy[N];
typedef long long LL;
LL sum[N], f[N];
int n, m, sn;
void dfs(int x, int fa)
{
	for (int i = 0; i < a[x].size(); ++i)
	{
		int v = a[x][i];
		if (a[x].size() > sn)
			heavy[v].push_back(x);
		if (v == fa) continue;
		dfs(v, x);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		sn = (int)sqrt(n);
		for (int i = 1; i <= n; ++i) 
		{
			a[i].clear();
			heavy[i].clear();
			f[i] = sum[i] = 0;
		}
		for (int i = 0; i < m; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j < a[i].size(); ++j)
			if (a[a[i][j]].size() > sn)
				heavy[i].push_back(a[i][j]);
		}
		int q;
		scanf("%d", &q);
		while (q--)
		{
			int x, y, z;
			scanf("%d%d", &x, &y);
			if (x)
			{
				if (a[y].size() > sn) printf("%lld\n", sum[y]);
				else 
				{
					LL ret = 0;
					for (int i = 0; i < a[y].size(); ++i)
						ret += f[a[y][i]];
					printf("%lld\n", ret);
				}
			}
			else
			{
				scanf("%d", &z);
				f[y] += z;
				for (int i = 0; i < heavy[y].size(); ++i)
					sum[heavy[y][i]] += z;
			}
		}
	}
	return 0;
}
