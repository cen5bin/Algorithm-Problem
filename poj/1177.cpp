#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 5010;
struct line
{
	int y1, y2;
	int h;
	int f;
}l[N<<1], l1[N<<1];

struct point
{
	int y;
	int id, f;
	point(){}
	point(double _y, int _id, int _f):y(_y), id(_id), f(_f){}
}pp[N<<2], pp1[N<<2];

int cmp(const point &p1, const point &p2)
{
	return p1.y < p2.y;
}
int cmp1(const line &l1, const line &l2)
{
	return l1.h < l2.h;
}

int kk[N<<1];

int sum[N<<3];
int len[N<<3];
void push_up(int l, int r, int rt)
{
	if (sum[rt]) len[rt] = kk[r+1] - kk[l];
	else len[rt] = len[rt<<1] + len[rt<<1|1];
}
void build(int l, int r, int rt)
{
	sum[rt] = 0;
	len[rt] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}
void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		sum[rt] += v;
		push_up(l, r, rt);
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(l, r, rt);
}
#define ABS(x) ((x)<0?(-(x)):(x))
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int cnt0 = 0;
		int cnt1 = 0, cnt2 = 0, cnt3 = 0; 
		for (int i = 0; i < n; i++)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			pp[cnt0++] = point(y1, cnt1, 0);
			pp[cnt0++] = point(y2, cnt1, 1);
			pp1[cnt3++] = point(x1, cnt2, 0);
			pp1[cnt3++] = point(x2, cnt2, 1);
			l[cnt1].h = x1, l[cnt1].f = 1, cnt1++;
			l[cnt1].h = x2, l[cnt1].f = -1, cnt1++;
			l1[cnt2].h = y1, l1[cnt2].f = 1, cnt2++;
			l1[cnt2].h = y2, l1[cnt2].f = -1, cnt2++;
		}
		int ans = 0;	
		sort(pp, pp+cnt0, cmp);
		int last = -1;
		int cnt = 0;
		for (int i = 0; i < cnt0; i++)
		{
			if (last != pp[i].y) cnt++, last = pp[i].y;
			if (pp[i].f == 0) l[pp[i].id].y1 = l[pp[i].id+1].y1 = cnt;
			else l[pp[i].id].y2 = l[pp[i].id+1].y2 = cnt;
			kk[cnt] = last;
		}
		build(1, cnt, 1);
		sort(l, l+cnt1, cmp1);
		int h = l[0].h;
		last = 0;
		for (int i = 0; i < cnt1; i++)
		{
			update(l[i].f, l[i].y1, l[i].y2-1, 1, cnt, 1);
			ans += ABS(last - len[1]);
			//h = l[i].h;
			last = len[1];
		}


		sort(pp1, pp1+cnt0, cmp);
		last = -1;
		cnt = 0;
		for (int i = 0; i < cnt3; i++)
		{
			if (last != pp1[i].y) cnt++, last = pp1[i].y;
			if (pp1[i].f == 0) l1[pp1[i].id].y1 = l1[pp1[i].id+1].y1 = cnt;
			else l1[pp1[i].id].y2 = l1[pp1[i].id+1].y2 = cnt;
			kk[cnt] = last;
		}
		build(1, cnt, 1);
		sort(l1, l1+cnt2, cmp1);
		h = l1[0].h;
		last = 0;
		for (int i = 0; i < cnt2; i++)
		{
			update(l1[i].f, l1[i].y1, l1[i].y2-1, 1, cnt, 1);
			ans += ABS(last - len[1]);
			//h = l[i].h;
			last = len[1];
		}
		printf("%d\n", ans);
	}
}
