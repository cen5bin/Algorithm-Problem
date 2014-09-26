#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
const int N = 10010;
const int Q = 1000;
struct node
{
	int v, id;
	node(){}
	node(int _v, int _id):v(_v), id(_id){}
};
vector<int>a[N];
vector<node> q[N];
void add_query(int id, int x, int y)
{
	q[x].push_back(node(y, id));
	q[y].push_back(node(x, id));
}
int p[N];
int find(int x)
{
	return x == p[x]?x:(p[x]=find(p[x]));
}
int ans[Q];
bool in[N];
void init()
{
	memset(p, -1, sizeof(p));
	memset(in, 0, sizeof(in));
}
void dfs(int x, int fa)
{
	p[x] = x;
	int size = a[x].size();
	for (int i = 0; i < size; i++)
	if (p[a[x][i]] == -1)
	{
		dfs(a[x][i], x);
		p[a[x][i]] = x;
	}
	size = q[x].size();
	for (int i = 0; i < size; i++)
	{
		if (p[q[x][i].v] != -1)
			ans[q[x][i].id] = find(q[x][i].v);
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		init();
		for (int i = 0; i < n-1; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x].push_back(y);
			in[y] = 1;
		}
		int qnum = 1;
		for (int i = 0; i < qnum; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add_query(i, x, y);
		}
		for (int i = 1; i <= n; i++)
		if (!in[i])
		{
			dfs(i, i);
			break;
		}
		printf("%d\n", ans[0]);
		for (int i = 1; i <= n; i++) a[i].clear();
		for (int i = 1; i <= n; i++) q[i].clear();
	}
	return 0;
}
