#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 100010;
LL sum[N<<2];//, add[N<<2];
void push_down(int rt)
{
	if (sum[rt] == 0) return;
	sum[rt<<1] += sum[rt];
	sum[rt<<1|1] += sum[rt];
	sum[rt] = 0;
}
void build(int l, int r, int rt)
{
	sum[rt] = 0;
	if (l == r) return;
	
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void update(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		sum[rt]++;
		return;
	}
	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, l, mid, rt<<1);
	if (R > mid) update(L, R, mid+1, r, rt<<1|1);
}

LL query(int p, int l, int r, int rt)
{
	if (l==r) return sum[rt];
	push_down(rt);
	int mid = (l + r) >> 1;
	if (mid >= p) return query(p, l, mid, rt<<1);
	return query(p, mid+1, r, rt<<1|1);
}

int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		build(1, n, 1);
		int t  = n;
		while (t--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			update(x, y, 1, n, 1);
		}
		for (int i = 1; i <= n; i++)
		{
			if (i > 1) printf(" ");
			printf("%lld", query(i, 1, n, 1));
		}
		puts("");
	}
	return 0;
}
