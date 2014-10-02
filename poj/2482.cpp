#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 10010;
int maxx;

struct star
{
	LL x, h;
	int v;
}ss[N];

struct point
{
	point(){}
	point(LL _x, int _id, int _f):x(_x), id(_id), f(_f){}
	LL x;
	int id, f;
}p[N<<1];
int MAX(int a, int b)
{
	return a > b ? a : b;
}

int sum[N<<3], add[N<<3];
void push_down(int rt)
{
	add[rt<<1] += add[rt];
	add[rt<<1|1] += add[rt];
	sum[rt<<1] += add[rt];
	sum[rt<<1|1] += add[rt];
	add[rt] = 0;
}
void push_up(int rt)
{
	sum[rt] = MAX(sum[rt<<1], sum[rt<<1|1]);
}
void build(int l, int r, int rt)
{
	sum[rt] = add[rt] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}
void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		add[rt] += v;
		sum[rt] += v;
		return;
	}
	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(rt);
}

int cmp1(const point &s1, const point &s2)
{
	return s1.x < s2.x;
}
int kk[N<<1];
int cmp2(const star &s1, const star &s2)
{
	if (s1.h == s2.h) return s1.x < s2.x;
	return s1.h < s2.h;
}



int main()
{
	int n;
	LL w, h;
	while (scanf("%d%lld%lld", &n, &w, &h) == 3)
	{
		int cnt0 = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%lld%lld%d", &ss[i].x, &ss[i].h, &ss[i].v);
			p[cnt0++] = point(ss[i].x, i, 0);
			p[cnt0++] = point(ss[i].x+w, i, 1);
		}
		sort(p, p+cnt0, cmp1);
		int last = -1;
		maxx = 0;
		for (int i = 0; i < cnt0; i++)
		{
			if (last != p[i].x) maxx++;
			if (p[i].f == 0) ss[p[i].id].x = maxx;
			else kk[ss[p[i].id].x] = maxx;
			last = p[i].x;
		}
		sort(ss, ss+n, cmp2);
		int now = 0;
		build(1, maxx, 1);
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			LL h0 = ss[i].h + h - 1;
			for ( ; now<n; now++)
			if (ss[now].h <= h0)
			{
				update(ss[now].v, ss[now].x, kk[ss[now].x]-1, 1, maxx, 1);
			}
			else break;
			ans = MAX(ans, sum[1]);
			update(-ss[i].v, ss[i].x, kk[ss[i].x]-1, 1, maxx, 1);
		}

		printf("%d\n", ans);
	}
	return 0;
}
