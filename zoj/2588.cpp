#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))
const int M = 100010;  //图中的边数
const int N = 10010; //点数
struct edge
{
	int id;		//边的编号，这个字段有时候可以省去
	int to;		//边的另一个断点
	int next;	//邻接表中的下一条边	
}e[M<<1];
int head[N]; //邻接表头，head[u] 表示点u的第一条边
int cnt;  //当前add边的下标
bool vis[N];  //节点是否已经被访问过
int tt;  //dfs的时间戳
int dfn[N]; //节点被dfs到的时间
int low[N]; //节点的子树中能够达到的最早搜索到的节点的时间戳
int ans[M];
int tol;
void init()
{
	cnt = 0, tt = 0;
	memset(head, -1, sizeof(head));
	memset(vis, 0, sizeof(vis));
	tol = 0;
}

//插入无向边，正向反向都被插入
void add_edge(int u, int v, int id = 0)
{
	e[cnt].to = v, e[cnt].id = id, e[cnt].next = head[u], head[u] = cnt++;
	e[cnt].to = u, e[cnt].id = id, e[cnt].next = head[v], head[v] = cnt++;
}

void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++tt;
	vis[u] = 1;
	for (int i = head[u]; i != -1; i = e[i].next)
	{
		if (e[i].id == fa) continue;
		int v = e[i].to;
		if (vis[v]) low[u] = min(low[u], dfn[v]);
		else
		{
			tarjan(v, e[i].id);
			low[u] = min(low[u], low[v]);
		}
		if (dfn[u] < low[v]) ans[tol++] = e[i].id;
	}

}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		init();
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add_edge(x, y, i);
		}
		tarjan(1, 0);
		printf("%d\n", tol);
		sort(ans, ans + tol);
		for (int i = 0; i < tol; ++i)
		{
			if (i) printf(" ");
			printf("%d", ans[i]);
		}
		if (tol) puts("");
		if (T) puts("");
	}
	return 0;
}
