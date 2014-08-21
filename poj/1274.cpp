#include <cstdio>
#include <cstring>

#define inf 0x7fffffff
#define min(a, b) (((a) < (b))?(a):(b))

typedef int TYPE; //答案的类型
const int M = 100010;  //最大边数
const int N = 410; //最大点数 

int n, m;

struct SAP
{
	struct edge
	{
		int to, next;
		TYPE cap;
		edge()
		{
			next = -1;
			cap = 0;
		}
	}e[M];
	int cnt;
	int head[N]; //邻接表头
	int pre[N]; //增广路前驱节点
	int d[N]; //距离标号
	int cur[N]; //当前狐
	int gap[N]; //距离为i的数量
	SAP()
	{
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(d, 0, sizeof(d));
		memset(gap, 0, sizeof(gap));
	}

	void insert_edge(int u, int v, TYPE c)
	{
		e[cnt].to = v;
		e[cnt].cap = c;
		e[cnt].next = head[u];
		head[u] = cnt++;
		e[cnt].to = u;
		e[cnt].cap = 0;
		e[cnt].next = head[v];
		head[v] = cnt++;
	}
	
	TYPE max_flow(int source, int sink)
	{
		TYPE ret = 0;
		TYPE flow = inf;
		gap[0] = n;
		int u = source;
		pre[source] = source;
		for (int i = 0; i <= n; i++)
			cur[i] = head[i];

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
				if (e[i].to == sink)
				{
					ret += flow;
					while (u != source)
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
			if (e[i].cap > 0 && mindis > d[e[i].to])
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
	int _n, _m;
	while (scanf("%d%d", &_n, &_m) == 2)
	{
		n = _n + _m + 2;
		SAP sap;
		for (int i = 1; i <= _n; i++)
		{
			int k;
			scanf("%d", &k);
			sap.insert_edge(0, _m+i, 1);
			for (int j = 0; j < k; j++)
			{
				int x;
				scanf("%d", &x);
				sap.insert_edge(i+_m, x, 1);
			}
		}
		for (int i = 1; i <= _m; i++)
			sap.insert_edge(i, n-1, 1);
		printf("%d\n", sap.max_flow(0, n-1));
	}
	return 0;
}
