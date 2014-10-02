#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct line
{
	int x1, x2, h, v;
	line(){}
	line(int _x1, int _x2, int _h, int _v):x1(_x1),x2(_x2),h(_h),v(_v){}
}l[N];

int cmp(const line &l1, const line &l2)
{
	return l1.h < l2.h;
}

int sum[N<<2];
void push_down(int rt)
{
	if (sum[rt] != -1)
	sum[rt<<1] = sum[rt<<1|1] = sum[rt];
	sum[rt] = -1;
}

void build(int l, int r, int rt)
{
	sum[rt] = -1;
	if (l==r) 
	{
		sum[rt] = 0;
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
}

int query(int p, int l, int r, int rt)
{
	if (l == r) return sum[rt];
	//if (p >= l && p <= r && sum[rt] != -1) return sum[rt];
	push_down(rt);
	int mid = (r + l) >> 1;
	if (p <= mid) return query(p, l, mid, rt<<1);
	return query(p, mid+1, r, rt<<1|1);
}

int dp[N];
int MAX(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int maxx = -1;
		for (int i = 1; i <= n; i++)
		{
			int x1, x2, h, v;
			scanf("%d%d%d%d", &h, &x1, &x2, &v);
			maxx = MAX(maxx, x2);
			l[i] = line(x1, x2, h, v);
		}
		sort(l+1, l+1+n, cmp);
		build(1, maxx, 1);
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			int id1 = query(l[i].x1, 1, maxx, 1);
			int id2 = query(l[i].x2, 1, maxx, 1);
			dp[i] = MAX(dp[id1], dp[id2]) + l[i].v;
			update(i, l[i].x1, l[i].x2, 1, maxx, 1);
		}
		if (dp[n] + 100 > 0)
		printf("%d\n", dp[n]+100);
		else puts("-1");
	}
	return 0;
}
