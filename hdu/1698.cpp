#include <cstdio>
#include <cstring>
const int N = 100010;
int sum[N<<2];
int flag[N<<2];
void push_up(int rt)
{
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
	flag[rt] = (flag[rt<<1] == flag[rt<<1|1]) ? flag[rt<<1] : -1;
}
void push_down(int rt)
{
	if (flag[rt] != -1)
		flag[rt<<1] = flag[rt<<1|1] = flag[rt];
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		flag[rt] = 1;
		sum[rt] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(rt);
}
void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		sum[rt] = v * (r - l + 1);
		flag[rt] = v;
		return;
	}
	int mid = (l + r) >> 1;
	push_down(rt);
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid + 1, r, rt<<1|1);
	push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r && flag[rt] > 0)
		 return flag[rt] * (r-l+1);
	int mid = (l + r) >> 1;
	int ret = 0;
	if (L <= mid) ret = query(L, R, l, mid, rt<<1);
	if (R > mid) ret+=query(L, R, mid+1, r, rt<<1|1);
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		int n;
		scanf("%d", &n);
		build(1, n, 1);
		int m;
		scanf("%d", &m);
		while (m--)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			update(z, x, y, 1, n, 1);
		}
		printf("Case %d: The total value of the hook is %d.\n", ++cas, query(1, n, 1, n, 1));
	}
	return 0;
}
