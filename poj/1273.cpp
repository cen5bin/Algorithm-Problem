#include <cstdio>
#include <cstring>

#define INF 0x7FFFFFFF
typedef long long LL;

const int V = 210;

LL c[V][V]; //最大的流量
LL f[V][V]; //已经流过的流量
LL low[V]; //可增广量
int pre[V]; //前驱节点
int q[V]; //队列
int n, m;



LL max_flow(int source, int sink)
{
	memset(f, 0, sizeof(f));
	LL flow = 0;
	do
	{
		bool vis[V]; 
		int head = 0;
		int tail = 0;
		memset(vis, 0, sizeof(vis));
		memset(low, 0, sizeof(low));
		q[tail++] = source;
		vis[source] = 1;
		low[source] = INF; 
		while (head < tail)
		{
			int now = q[head++];
			for (int i = 1; i <= n; i++)
			if (!vis[i] && c[now][i] > f[now][i])
			{
				LL tmp = c[now][i] - f[now][i];
				vis[i] = 1;
				pre[i] = now;
				low[i] = tmp;
				q[tail++] = i;
				if (low[i] > low[now]) low[i] = low[now];
			}
		}
		if (low[sink] > 0)
		{
			int u = sink;
			while (u != source)
			{
				f[pre[u]][u] += low[sink]; f[u][pre[u]] -= low[sink]; u = pre[u];
			}
			flow += low[sink];
		}

	}while (low[sink] > 0);
	return flow;
}

int main()
{
	while (scanf("%d%d", &m, &n) == 2)
	{
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; i++)
		{
			int x, y;
			LL z;
			scanf("%d%d%lld", &x, &y, &z);
			c[x][y] += z;
//			c[y][x] -= z;
		}
		printf("%lld\n", max_flow(1, n));

	}
	return 0;
}
