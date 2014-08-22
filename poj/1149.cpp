#include <cstdio>
#include <cstring>
#define min(a, b) (((a) < (b))? (a): (b))
#define inf 0x7fffffff

const int N = 1500;
const int M = 100010;

int m, n;
struct SAP
{
	struct edge
	{
		int to, next;
		int cap;
	}e[M];
	int head[N];
	int pre[N];
	int cur[N];
	int d[N];
	int gap[N];
	int cnt;

	SAP()
	{
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(d, 0, sizeof(d));
		memset(gap, 0, sizeof(gap));
	}

	void insert(int u, int v, int c)
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

	int max_flow(int source, int sink)
	{
		int ret = 0;
		for (int i = 0; i <= n; i++)
			cur[i] = head[i];
		gap[0] = n;
		int u = source;
		pre[u] = source;
		int flow = inf;
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
					while (u != source)
					{
						u = pre[u];
						e[cur[u]].cap -= flow;
						e[cur[u]^1].cap += flow;
					}
				}
				break;
			}
			if (find) continue;
			int mindist = n;
			for (int i = head[u]; i != -1; i = e[i].next)
			if (e[i].cap > 0 && d[e[i].to] < mindist)
			{
				mindist = d[e[i].to];
				cur[u] = i;
			}
			if (--gap[d[u]] == 0) break;
			d[u] = mindist + 1;
			gap[d[u]]++;
			u = pre[u];
		}

		return ret;
	}
};


int pigs[N];
int first[N];

int main()
{
	int x, y;
	while (scanf("%d%d", &x, &y) == 2)
	{
		memset(first, -1, sizeof(first));
		SAP sap;
		for (int i = 1; i <= x; i++)
			scanf("%d", &pigs[i]);
		for (int i = 1; i <= y; i++)
		{
			int a;
			scanf("%d", &a);
			int flow = 0;
			for (int j = 0; j < a; j++)
			{
				int key;
				scanf("%d", &key);
				if (first[key] == -1)
				{
					flow += pigs[key];
					first[key] = i;
				}
				else sap.insert(first[key], i, inf);
			}
			if (flow) sap.insert(0, i, flow);
			int b;
			scanf("%d", &b);
			sap.insert(i, y+1, b);
		}
		n = y+2;
		printf("%d\n", sap.max_flow(0, n-1));
	}
	return 0;
}
