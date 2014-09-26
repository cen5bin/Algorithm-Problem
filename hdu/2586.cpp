#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 40010;
const int Q = 210;
struct node
{
	int v, id;
	node(){}
	node(int _v, int _id):v(_v),id(_id){}
};
struct edge
{
	int v, l, next;
}e[N<<1];
int cnt;
int head[N];
vector<node> q[N];
int p[N];
int ans[Q];
int d[N];
void add_edge(int u, int v, int l)
{
	e[cnt].v = v, e[cnt].l = l, e[cnt].next = head[u], head[u] = cnt++;
	e[cnt].v = u, e[cnt].l = l, e[cnt].next = head[v], head[v] = cnt++;
}
void add_query(int id, int x, int y)
{
	q[x].push_back(node(y, id));
	q[y].push_back(node(x, id));
}
int find(int x)
{
	return x == p[x]?x:(p[x]=find(p[x]));
}
void dfs(int x, int fa, int d0)
{
	p[x] = x;
	d[x] = d0;
	for (int i = head[x]; i != -1; i = e[i].next)
	if (p[e[i].v] == -1)
	{
		dfs(e[i].v, x, d0+e[i].l);
		p[e[i].v] = x;
	}
	int size = q[x].size();
	for (int i = 0; i < size; i++)
	if (p[q[x][i].v] != -1)
	{
		int an = find(q[x][i].v);
		ans[q[x][i].id] = d[x]+d[q[x][i].v]-2*d[an];
	}
}

void init()
{
	cnt = 0;
	memset(p, -1, sizeof(p));
	memset(head, -1, sizeof(head));
}



int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < n - 1; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add_edge(x, y, z);
		}
		for (int i = 0; i < m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add_query(i, x, y);
		}
		dfs(1, 1, 0);
		for (int i = 0; i < m; i++)
			printf("%d\n", ans[i]);
		for(int i = 1; i <= n; i++)
			q[i].clear();

	}
	return 0;
}
