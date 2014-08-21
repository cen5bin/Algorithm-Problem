#include <cstdio>
#include <cstring>
#define inf 0x7fffffff
#define min(a, b) (((a) < (b))?(a):(b))

typedef int TYPE;

const int M = 100010;
const int N = 1000;

int n, m;
struct SAP
{
	struct edge
	{
		int to,next;
		TYPE cap;
	}e[M];
	int head[N];
	int cnt;
	int pre[N];
	int cur[N];
	int d[N];
	int gap[N];
	SAP()
	{
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(d, 0, sizeof(d));
		memset(gap, 0, sizeof(gap));
	}
	void insert(int u, int v, TYPE c)
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
		for (int i = 0; i <= n; i++)
			cur[i] = head[i];
		gap[0] = n;
		pre[source] = source;
		int u = source;
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
						e[cur[u] ^ 1].cap += flow;
					}
					flow = inf;
				}
				break;
			}
			if (find) continue;
			int mindst = n;
			for (int i = head[u]; i != -1; i = e[i].next)
			if (e[i].cap > 0 && mindst > d[e[i].to])
			{
				mindst = d[e[i].to];
				cur[u] = i;
			}
			if (--gap[d[u]] == 0) break;
			d[u] = mindst + 1;
			gap[d[u]]++;
			u = pre[u];
		}
		return ret;
	}

};

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		SAP sap;
		int k;
		scanf("%d", &k);
		int data[25][10];
		int max_w = 0;
		for (int i = 1; i <= k; i++)
		for (int j = 0; j < 9; j++)
			scanf("%d", &data[i][j]);
		for (int i = 1; i <= k; i++)
			if (data[i][8] > max_w) max_w = data[i][8];
		n = 1 + 7 * max_w + k + 1;
		for (int i = 0; i < max_w; i++)
		for (int j = 0; j < 7; j++)
			sap.insert(0, k + 7 * i + j + 1, 1);

		int tol = 0;
		for (int i = 1; i <= k; i++)
		{	
			for (int j = 0; j < data[i][8]; j++)
			{
				for (int l = 0; l < 7; l++)
				if (data[i][l])
				sap.insert(k+j*7+l+1, i, 1);
			}
			sap.insert(i, n-1, data[i][7]);
			tol+=data[i][7];
		}
		if (sap.max_flow(0, n-1) == tol)
			puts("Yes");
		else puts("No");
	}
	return 0;
}
