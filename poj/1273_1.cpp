#include <cstdio>
#include <cstring>

const int V = 210;
typedef long long LL;


int n, m;
LL c[V][V];
LL low[V];
LL f[V][V];
int pre[V];
bool vis[V];
int q[V];

LL bfs(int source, int sink)
{
	memset(vis, 0, sizeof(vis));
	memset(low, 0, sizeof(low));
	int head = 0;
	int tail = 0;
	q[tail++] = source;
	vis[source] = 1;
	low[source] = -1;
	while (head < tail)
	{
		int u = q[head++];
		for (int i = 1; i <= n; i++)
		if (!vis[i] && c[u][i] > f[u][i])
		{
			low[i] = c[u][i] - f[u][i];
			vis[i] = 1;
			q[tail++] = i;
			pre[i] = u;
			if (low[u] != -1 && low[u] < low[i]) low[i] = low[u];
		}
	}
	return low[sink];
}


LL max_flow(int source, int sink)
{
	LL ret = 0;
	memset(f, 0, sizeof(f));
	LL flow = 0;
	while (flow = bfs(source, sink))
	{
		ret += flow;
		int u = sink;
		while (u != source){f[pre[u]][u] += flow; f[u][pre[u]]-=flow; u = pre[u];   }
	}
	return ret;
}

int main()
{
	while (scanf("%d%d", &m, &n) != EOF)
	{
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; i++)
		{
			int x, y;
			LL z;
			scanf("%d%d%lld", &x, &y, &z);
			c[x][y] += z;
		}
		printf("%lld\n", max_flow(1, n));
	}
	return 0;
}
