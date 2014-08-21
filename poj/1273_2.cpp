#include <cstdio>
#include <cstring>

int n, m;
const int N = 210; //最大点数
const int M = 2100; //最大边数
#define inf 0x7fffffffffffLL

typedef long long LL;

struct SAP
{
	struct edge
	{
		int to;
		LL cap;
		int next;
	}e[M<<1];
	int head[N]; //邻接表的头
	int cnt;
	int	d[N];  //编号为i的点的距离
	int cur[N]; // 编号为i的点的当前狐，记录的是连接表中边的下标
	int pre[N]; //前驱节点编号
	int gap[N]; //距离为i的点的个数

	SAP()
	{
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(d, 0, sizeof(d));
		memset(gap, 0, sizeof(gap));
		for (int i = 0; i < M; i++)
			e[i].cap = 0, e[i].next = -1;
	}

	void insert_edge(int u, int v, LL cap)
	{
		e[cnt].to = v;
		e[cnt].cap = cap;
		e[cnt].next = head[u];
		head[u] = cnt++;
		e[cnt].to = u;
		e[cnt].cap = 0;
		e[cnt].next = head[v];
		head[v] = cnt++;
	}

	inline	LL min(LL a, LL b)
	{
		return a < b ? a : b;
	}

	LL max_flow(int source, int sink)
	{
		LL ret = 0;
		for (int i = 0; i <= n; i++)
			cur[i] = head[i];
		gap[0] = n;
		int u = source;
		pre[source] = source;
		LL flow = inf;
		while (d[source] < n)
		{
			bool find = 0;
			for (int &i = cur[u]; i != -1; i = e[i].next)
			if (e[i].cap > 0 && d[u] == d[e[i].to] + 1)
			{
				find = 1;
				flow = min(flow, e[i].cap);
				pre[e[i].to] = u;
				u = e[i].to;
				if (u == sink)
				{
					ret += flow;
					while(u != source)
					{
						u = pre[u];
						e[cur[u]].cap -= flow;
						e[cur[u]^1].cap += flow;
					}
					flow = inf;
				}
				break;
			}
			if (find) continue;
			int mindis = n;
			for (int i = head[u]; i != -1; i = e[i].next)
			if (e[i].cap > 0 && d[e[i].to] < mindis)
			{
				mindis = d[e[i].to];
				cur[u] = i;
			}
			if (--gap[d[u]] == 0) break;
			d[u] = mindis + 1;
			gap[d[u]]++;
			u = pre[u];
		}
		return ret;
	}
};




int main()
{
	while (scanf("%d%d", &m, &n) != EOF)
	{
		SAP sap;
		for (int i = 0; i < m; i++)
		{
			int x,y;
			LL z;
			scanf("%d%d%lld", &x, &y, &z);
			sap.insert_edge(x, y, z);
		}
		printf("%lld\n", sap.max_flow(1, n));
	}
	return 0;
}
