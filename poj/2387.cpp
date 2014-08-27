#include <cstdio>
#include <cstring>

#define min(a, b) (((a) < (b))? (a) : (b))
#define inf 0x7fffffff

const int N = 1010;
const int M = 2010;

typedef int TYPE;

struct SPFA
{
	int pre[N]; // 前驱节点
	bool vis[N]; //是否在队列中
	TYPE dis[N]; //距离
	int q[N*4]; //队列
	int h, t; //队列头和尾
	struct edge
	{
		int to, next;
		TYPE len;
	}e[M*2];
	int head[N];
	int cnt;

	void init()
	{
		memset(pre, 0, sizeof(pre));
		memset(vis, 0, sizeof(vis));
		cnt = 0;
		h = t = 0;
		memset(head, -1, sizeof(head));
		for (int i = 0; i < N; i++)
			dis[i] = inf;
		//for (int i = 0; i < M; i++)
		//	e[i].len = inf;
	}

	void insert(int u, int v, TYPE len)
	{
		e[cnt].to = v;
		e[cnt].len = len;//min(e[cnt].len, len);
		e[cnt].next = head[u];
		head[u] = cnt++;
		e[cnt].to = u;
		e[cnt].len = len;//min(e[cnt].len, len);
		e[cnt].next = head[v];
		head[v] = cnt++;
	}

	void work(int source)
	{
		dis[source] = 0;
		q[t++] = source;
		while (h < t)
		{
			int u = q[h++];
			vis[u] = 0;
			for (int i = head[u]; i != -1; i = e[i].next)
			if (dis[e[i].to] > e[i].len + dis[u])
			{
				dis[e[i].to] = e[i].len + dis[u];
				pre[e[i].to] = u;
				if (!vis[e[i].to])
				{
					q[t++] = e[i].to;
					vis[e[i].to] = 1;
				}
			}
		}
	}
}spfa;


int main()
{
	int n, t;
	while (scanf("%d%d", &t, &n) == 2)
	{
		spfa.init();
		for (int i = 0; i < t; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			spfa.insert(x, y, z);
		}
		spfa.work(n);
		printf("%d\n", spfa.dis[1]);
	}
	return 0;
}
