#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
const int N = 10010;
struct post
{
	int x1, x2;
}p[N];

set<int> ss;
int xx[N<<1];
int aa[N][2];
map<int, int> mm;

int sum[N<<3];
void push_up(int rt)
{
	if (sum[rt<<1] == sum[rt<<1|1]) sum[rt] = sum[rt<<1];
	else sum[rt] = -1;
}
void push_down(int rt)
{
	if (sum[rt] == -1) return;
	sum[rt<<1] = sum[rt<<1|1] = sum[rt];
	//sum[rt] = -1;
}
void build(int l, int r, int rt)
{
	sum[rt] = 0;
	if (l == r) 
	{
	//	sum[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}
void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		sum[rt] = v;
		return;
	}
	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(rt);
}

bool vis[N<<1];

int query(int l, int r, int rt)
{
	if (sum[rt] != -1)
	{
		if (vis[sum[rt]]) return 0;
		vis[sum[rt]] = 1;
		return 1;
	}
	if (l == r) return 0;
	int mid = (l + r) >> 1;
	return query(l, mid, rt<<1) + query(mid+1, r, rt<<1|1);
}

struct point
{
	int x, id, f;
}pp[N<<1];

int cmp(const point &p1, const point &p2)
{
	return p1.x < p2.x;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		int cnt0 = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &p[i].x1, &p[i].x2);
			pp[cnt0].x = p[i].x1;
			pp[cnt0].id = i;
			pp[cnt0].f = 0;
			cnt0++;
			pp[cnt0].x = p[i].x2;
			pp[cnt0].id = i;
			pp[cnt0].f = 1;
			cnt0++;
			//xx[cnt0++] = p[i].x1;
			//xx[cnt0++] = p[i].x2;
		}
		sort(pp, pp+cnt0, cmp);
		//sort(xx, xx+cnt0);
		int cnt = 0;
		for (int i = 0, last = -1; i < cnt0; i++)	
			if (pp[i].x != last)
				aa[pp[i].id][pp[i].f] = ++cnt, last = pp[i].x;
			else aa[pp[i].id][pp[i].f] = cnt;
		build(1, cnt, 1);
		for (int i = 0; i < n; i++)
			update(i+1, aa[i][0], aa[i][1], 1, cnt, 1);
			//update(i+1, mm[p[i].x1], mm[p[i].x2], 1, cnt, 1);
		memset(vis, 0, sizeof(vis));
		vis[0] = 1;
		printf("%d\n", query(1, cnt, 1));
		//ss.clear();
	//	mm.clear();
	}
	return 0;
}
