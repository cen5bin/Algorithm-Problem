#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

const int N = 50010;
typedef int LL;

struct edge
{
	int v, next;
	LL l;
}e[N<<1];
int cnt;
int head[N];
bool vis[N];
map<LL, int> mm;
LL qq[N], qq1[N];
void init()
{
	mm.clear();
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(vis, 0, sizeof(vis));
}

struct node
{
	LL maxx[4];
	int p[4];
}a[N];

void add_edge(int u, int v, LL l)
{
	e[cnt].v = v, e[cnt].l = l, e[cnt].next = head[u], head[u] = cnt++;
	e[cnt].v = u, e[cnt].l = l, e[cnt].next = head[v], head[v] = cnt++;
}

template <class T>
void swap0(T &a, T &b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}


void dfs1(int x, int fa)
{
	vis[x] = 1;
	memset(a[x].maxx, 0, sizeof(a[x].maxx));
	memset(a[x].p, 0, sizeof(a[x].p));
	for (int i = head[x]; i != -1; i = e[i].next)
	{
		int v = e[i].v;
		if (vis[v]) continue;
		dfs1(v, x);
		a[x].maxx[2] = e[i].l + a[v].maxx[0];
		int end = 2;
		//if (0 != a[v].p[1])
		//	a[x].maxx[3] = e[i].l + a[v].maxx[1];
		//else end--;
		a[x].p[2] = a[x].p[3] = v;
		for (int j = 2; j <= end; j++)
		{
			int k = j;
			while (k && a[x].maxx[k] > a[x].maxx[k-1])
			{
				swap0(a[x].maxx[k], a[x].maxx[k-1]);
				swap0(a[x].p[k], a[x].p[k-1]);
				k--;
			}
		}
		
	}
}

void dfs2(int x, int fa)
{
	vis[x] = 1;
	for (int i = head[x]; i != -1; i = e[i].next)
	{
		int v = e[i].v;
		if (vis[v]) continue;
		LL tmp1 = a[v].maxx[0];
		LL tmp2;
		if (a[x].p[0] == v)
			tmp2 = e[i].l + a[x].maxx[1];
		else tmp2 = e[i].l + a[x].maxx[0];
		if (tmp2 >= tmp1) a[v].maxx[0] = tmp2, a[v].p[0] = 0;
		else if (tmp2 > a[v].maxx[1]) a[v].maxx[1] = tmp2;
		dfs2(v, x);
	}
}

const int M = 16;
LL dp_max[N][M], dp_min[N][M];
int xx[M], aa[N];
void rmq_init(int n)
{
	for (int i = 1; i <= n; i++)
		dp_max[i][0] = dp_min[i][0] = a[i].maxx[0];
	for (int j = 1; j < M; j++)
	for (int i = 1; i <= n; i++)
	if (i+xx[j]-1<=n)
		dp_max[i][j] = MAX(dp_max[i][j-1], dp_max[i+xx[j-1]][j-1]),
		dp_min[i][j] = MIN(dp_min[i][j-1], dp_min[i+xx[j-1]][j-1]);
}

inline LL rmq_query(int l, int r)
{
	int k = aa[r-l+1];
	return MAX(dp_max[l][k], dp_max[r-xx[k]+1][k]) - MIN(dp_min[l][k], dp_min[r-xx[k]+1][k]);
}

int main()
{
	for (int i = 0; i < M; i++) xx[i] = 1 << i;
	aa[0] = 0;
	for (int i = 1; i < N; i++) 
	if ((1<<(aa[i-1]+1))>i) 
		aa[i] = aa[i-1];
	else aa[i] = aa[i-1]+1;
	int n, m;
	while (scanf("%d%d", &n, &m)==2 && n+m)
	{
		init();
		for (int i = 0; i < n-1; i++)
		{
			int x, y;
			LL z;
			scanf("%d%d%d", &x, &y, &z);
			add_edge(x, y, z);
		}
		dfs1(1, 0);
	//	for (int i = 1; i <= n; i++)
	//		printf("%lld ", a[i].maxx[0]);
	//	puts("");
		memset(vis, 0, sizeof(vis));
		dfs2(1, 0);
	//	for (int i = 1; i <= n; i++)
	//		printf("%lld ", a[i].maxx[0]);
		rmq_init(n);
		for (int i = 0; i < m; i++) 
		{
			scanf("%d", &qq[i]);
			qq1[i] = qq[i];
		}
		sort(qq, qq+m);
		int ans = 1;
		for (int i = 0; i < m; i++)
		{
			for (int l = 1, r = l + ans; r <= n; r++)
			{
				while (r-l+1 > ans && rmq_query(l, r) > qq[i]) l++;
				ans = MAX(ans, r-l+1);
			}
			mm[qq[i]] = ans;
		}
		for (int i = 0; i < m; i++)
			printf("%d\n", mm[qq1[i]]);
		
	}
	return 0;
}
