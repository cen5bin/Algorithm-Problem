#include <cstdio>
#include <cstring>

const int M = 100010;
const int N = 1010;

int n, m;
struct Hungary
{
	struct edge
	{
		int to, next;
	}e[M];
	bool vis[N];
	int link[N];
	int head[N];
	int cnt;
	Hungary()
	{
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(link, -1, sizeof(link));
		memset(vis, 0, sizeof(vis));
	}
	void insert(int u, int v)
	{
		e[cnt].to = v;
		e[cnt].next = head[u];
		head[u] = cnt++;
		e[cnt].to = u;
		e[cnt].next = head[v];
		head[v] = cnt++;
	}
	bool dfs(int u)
	{
		for (int i = head[u]; i != -1; i = e[i].next)
		if (!vis[e[i].to])
		{
			vis[e[i].to] = 1;
			if (link[e[i].to] == -1 || dfs(link[e[i].to]))
			{
				link[e[i].to] = u;
				return 1;
			}
		}
		return 0;
	}
	int solve()
	{
		int ret = 0;
		for (int i = 1; i <= n; i++)
		{
			memset(vis, 0, sizeof(vis));
			if (dfs(i)) ret++;
		}
		return ret;
	}
};

int main()
{
	int a, b;
	while (scanf("%d%d", &a, &b) == 2)
	{
		Hungary hungary;
		n = a;
		for (int i = 1; i <= a; i++)
		{
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++)
			{
				int x;
				scanf("%d", &x);
				hungary.insert(i+b, x);
			}
		}
		printf("%d\n", hungary.solve());
	}
	return 0;
}
