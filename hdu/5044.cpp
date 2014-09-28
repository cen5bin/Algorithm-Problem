#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 100010;
struct edge
{
	int v, next, id;
}e[N<<1];
int cnt;
int head[N];
LL add[2][N], sub[2][N], v1[N], v2[N];
void add_edge(int u, int v, int id)
{
	e[cnt].v = v, e[cnt].id = id, e[cnt].next = head[u], head[u] = cnt++;
	e[cnt].v = u, e[cnt].id = id, e[cnt].next = head[v], head[v] = cnt++;
}
void init(int n)
{
	for (int i = 0; i < 2; i++)
	for (int j = 0; j <= n; j++) add[i][j] = 0, sub[i][j] = 0;
	for (int i = 0; i <= n; i++) v1[i] = v2[i] = 0;
	for (int i = 0; i <= n; i++) head[i] = -1;
	//memset(add[0], 0, sizeof(LL)*(n+5));
	//memset(add[1], 0, sizeof(LL)*(n+5));
	//memset(sub[0], 0, sizeof(LL)*(n+5));
	//memset(sub[1], 0, sizeof(LL)*(n+5));
	//memset(v1, 0, sizeof(LL)*(n+5));
	//memset(v2, 0, sizeof(LL)*(n+5));
	cnt = 0;
	//memset(head, -1, sizeof(int) * (n+5));
}

//离线LCA
struct node
{
	int v, id;
	node(){}
	node(int _v, int _id):v(_v), id(_id){}
};
vector<node> q[N];
int ancestor[N];
int p[N];
void init_lca(int n)
{
	for (int i = 1; i <= n; i++) p[i] = -1;
	//memset(p, -1, sizeof(int) * (n+5));
	for (int i = 0; i <= n; i++) q[i].clear();
}
int find(int x)
{
	return x == p[x] ? p[x] : (p[x] = find(p[x]));
}
void add_query(int u, int v, int id)
{
	q[u].push_back(node(v, id));
	q[v].push_back(node(u, id));
}
void dfs(int x, int fa)
{
	p[x] = x;
	for (int i = head[x]; i != -1; i = e[i].next)
	if (p[e[i].v] == -1)
	{
		dfs(e[i].v, x);
		p[e[i].v] = x;
	}
	int size = q[x].size();
	for (int i = 0; i < size; i++)
	if (p[q[x][i].v] != -1)
		ancestor[q[x][i].id] = find(q[x][i].v);
}

////
const int M = 100010;
int tag[M];
struct pp
{
	int x, y, z;
	pp(){}
	pp(int _x, int _y, int _z):x(_x), y(_y), z(_z){}
}qq[M];

void dfs1(int x, int fa)
{
	for (int i = head[x]; i !=- 1; i = e[i].next)
	{
		int v = e[i].v;
		if (v == fa) continue;
		dfs1(v, x);
		//v1[x] += add[0][v];
		v2[e[i].id] = add[1][v];
		add[0][x] += add[0][v];
		add[1][x] += add[1][v];
	}
	v1[x] = add[0][x] - sub[0][x];
	add[0][x] -= sub[0][x] * 2;
	add[1][x] -= sub[1][x] * 2;
}
int Scan()     //输入外挂
{
	int res=0,ch,flag=0;
	if((ch=getchar())=='-') flag=1;
	else if(ch>='0'&&ch<='9') res=ch-'0';
	while((ch=getchar())>='0'&&ch<='9') res=res*10+ch-'0';
	return flag?-res:res;
}

LL Scanl()     //输入外挂
{
	LL res=0,ch,flag=0;
	if((ch=getchar())=='-') flag=1;
	else if(ch>='0'&&ch<='9') res=ch-'0';
	while((ch=getchar())>='0'&&ch<='9') res=res*10+ch-'0';
	return flag?-res:res;
}
inline int read() {
	int data;
	 char ch = getchar();
	  while (ch < '0' || ch > '9') ch = getchar();
	   data = 0;
	   do{
		     data = data*10 + ch-'0';
			   ch = getchar(); 
			    }while (ch >= '0' && ch <= '9');
	   return data;
}
inline void Out(int a)    //输出外挂
{
	     if(a>9)
			          Out(a/10);
		      putchar(a%10+'0');
}
inline void Out(LL a)    //输出外挂
{
	     if(a>9)
			          Out(a/10);
		      putchar(a%10+'0');
}
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	char s[10];
	while (t--)
	{
		int n, m;
		n = read();
		m = read();
		//scanf("%d%d", &n, &m);
		init(n);
		for (int i = 1; i < n; i++)
		{
			int x, y;
			x = read();
			y = read();
			//scanf("%d%d", &x, &y);
			add_edge(x, y, i);
		}
		init_lca(n);
		for (int i = 0; i < m; i++)
		{
			int x, y, z;
			//scanf("%s%d%d%d", s, &x, &y, &z);
			scanf("%s", s);
			x = read();
			y = read();
			z = read();
			if (s[3] == '1') tag[i] = 0;
			else tag[i] = 1;
			add_query(x, y, i);
			qq[i] = pp(x, y, z);
		}
		dfs(1, 1);
		for (int i = 0; i < m; i++)
		{
			add[tag[i]][qq[i].x] += qq[i].z;
			add[tag[i]][qq[i].y] += qq[i].z;
			sub[tag[i]][ancestor[i]] += qq[i].z;
		}
		dfs1(1, 1);
		printf("Case #%d:\n", ++cas);
		for (int i = 1; i <= n; i++)
		{
			if (i > 1) printf(" ");
			Out(v1[i]);
			//printf("%lld", v1[i]);
		}
		puts("");
		for (int i = 1; i < n; i++)
		{
			if (i > 1) printf(" ");
			Out(v2[i]);
			//printf("%lld", v2[i]);
		}
		puts("");
	}
	return 0;
}
