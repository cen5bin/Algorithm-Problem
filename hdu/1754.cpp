#include <cstdio>
#include <cstring>
int MAX(int a, int b)
{
	return a > b ? a : b;
}
const int N = 200010;
int sum[N<<2];
void push_up(int rt)
{
	sum[rt] = MAX(sum[rt<<1], sum[rt<<1|1]);
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		scanf("%d", &sum[rt]);
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(rt);
}

void update(int p, int v, int l, int r, int rt)
{
	if (l == r)
	{
		sum[rt] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(p, v, l, mid, rt<<1);
	else update(p, v, mid+1, r, rt<<1|1);
	push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r) return sum[rt];
	int mid = (l + r) >> 1;
	int ret = 0;
	if (L <= mid) ret = MAX(ret, query(L, R, l, mid, rt<<1));
	if (R > mid) ret = MAX(ret, query(L, R, mid+1, r, rt<<1|1));
//	push_up(rt);
	return ret;
}

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		build(1, n, 1);
			char c;
			int x, y;
		while (m--)
		{
			scanf(" %c%d%d", &c, &x, &y);
			if (c=='Q') printf("%d\n", query(x, y, 1, n, 1));
			else update(x, y, 1, n, 1);
		}
	}
	return 0;
}
