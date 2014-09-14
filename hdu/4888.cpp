#include <cstdio>
#include <cstring>

#define inf 0x7fffffff
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef int TYPE;

const int M = 200010;
const int N = 1000;

struct edge {
	int v, next;
	TYPE cap;
}e[M<<1];
int head[N], cur[N], pre[N], gap[N], d[N];
int num, cnt;
void init() {
	memset(head, -1, sizeof(head));
	cnt = 0;
}
void add_edge(int u, int v, TYPE cap) {
	e[cnt].cap = cap;
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt++;
	e[cnt].cap = 0;
	e[cnt].v = u;
	e[cnt].next = head[v];
	head[v] = cnt++;
}
void bfs(int sink) {
	int q[N];
	int start = 0, end = 0;
	q[end++] = sink;
	memset(gap, 0, sizeof(gap));
	memset(d, -1, sizeof(d));
	d[sink] = 0;
	while (start < end) {
		int u = q[start++];
		gap[d[u]]++;
		for (int i = head[u]; i != -1; i = e[i].next)
		if (e[i^1].cap && (d[e[i].v] == -1||d[e[i].v] < d[u] + 1)) {
			d[e[i].v] = d[u] + 1;
			q[end++] = e[i].v;
		}
	}
}

TYPE sap(int source, int sink) {
	for (int i = 0; i < num; ++i)
		cur[i] = head[i];
	bfs(sink);
	TYPE ret = 0;
	TYPE flow = inf;
	pre[source] = source;
	int u = source;
	while (d[source] < num) {
		bool find = 0;
		for (int &i = cur[u]; i != -1; i = e[i].next) 
		if (e[i].cap > 0 && d[u] == d[e[i].v] + 1) {
			find = 1;
			flow = min(flow, e[i].cap);
			pre[e[i].v] = u;
			u = e[i].v;
			if (u == sink) {
				ret += flow;
				while (u != source) {
					u = pre[u];
					e[cur[u]].cap -= flow;
					e[cur[u]^1].cap += flow;
				}
				flow = inf;
			}
			break;
		}
		if (find) continue;
		int mindis = num;
		for (int i = head[u]; i != -1; i = e[i].next)
		if (e[i].cap && d[e[i].v] < mindis) {
			mindis = d[e[i].v];
			cur[u] = i;
		}
		if (--gap[d[u]] == 0) break;
		d[u] = mindis + 1;
		gap[d[u]]++;
		u = pre[u];
	}
	return ret;
}

int vis[N];
bool vis_e[M<<1];
bool dfs(int u, int f) {
	vis[u] = 1;
	for (int i = head[u]; i != -1; i = e[i].next)
	if (!vis_e[i] && e[i].cap && e[i].v != f && vis[e[i].v] != -1) {
		if (vis[e[i].v] == 1) return 1;
		vis_e[i] = 1;
		if (dfs(e[i].v, u)) return 1;
		vis[e[i].v] = 0;
	}
	vis[u] = -1;
	return 0;
}

bool is_unique(int num) {
	memset(vis, 0, sizeof(vis));
	memset(vis_e, 0, sizeof(bool) * (cnt+1));
	for (int i = 0; i < num; i++)
		if (vis[i] != -1 && dfs(i, -1)) return 0;
	return 1;
}


int mat[410][410];

int main() {
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		init();
		num = n + m + 2;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			add_edge(0, i+1, x);
			sum1 += x;
		}
		for (int i = 0; i < m; i++) {
			int x;
			scanf("%d", &x);
			add_edge(i+n+1, num-1, x);
			sum2 += x;
		}
		if (sum1 != sum2) {
			puts("Impossible");
			continue;
		}
		for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			add_edge(i+1, j+n+1, k);
			mat[i][j] = cnt-1;
		}
		if (sap(0, num-1) != sum1) {
			puts("Impossible");
			continue;
		}
		bool yes = is_unique(num);
		if (!yes) puts("Not Unique");
		else {
			puts("Unique");
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (j) printf(" ");
					printf("%d", e[mat[i][j]].cap);
				}
				puts("");
			}
		}
	}
	
	return 0;
}
