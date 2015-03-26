#include <cstdio>
#include <cstring>

const int N = 510;
int nn, mm;     //二分图两边的点数
bool g[N][N];  //邻接表
bool vis[N];   //右边的点是否已经被dfs过
int linker[N]; //右边点的匹配点（左边点）的编号

//每次dfs相当于寻找一条增广路
//交替路：路上匹配边和非匹配边交替出现
//增广路：两端是非匹配点的交替路
//找到一条增广路，将路上的非匹配边变成匹配边，匹配边变成非匹配边，就可以使得整个匹配数加上1
bool dfs(int u)
{
	for (int i = 1; i <= mm; ++i)
	if (g[u][i] && !vis[i])
	{
		vis[i] = 1;
		if (linker[i] == -1 || dfs(linker[i]))
		{
			linker[i] = u;
			return 1;
		}
	}
	return 0;
}

int hungary()
{
	int ret = 0;
	memset(linker, -1, sizeof(linker));
	for (int i = 1; i <= nn; ++i)
	{
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ret++;
	}
	return ret;
}

int main()
{
	int k, n, m;
	while (scanf("%d", &k) && k)
	{
		scanf("%d%d", &n, &m);
		nn = n, mm = m;
		memset(g, 0, sizeof(g));
		while (k--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			g[x][y] = 1;
		}
		printf("%d\n", hungary());
	}
	return 0;
}

