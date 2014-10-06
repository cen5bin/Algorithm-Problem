#include <cstdio>
#include <cstring>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
const int N = 50010;
typedef long long LL;
LL  a[N], p[N], dp[N];

LL sum[N<<2];
//template <class T>
//T MIN(T a, T b)
//{
//	return a < b ? a : b;
//}
void push_up(int rt)
{
	sum[rt] = MIN(sum[rt<<1], sum[rt<<1|1]);
}
void build(int l, int r, int rt)
{
	sum[rt] = 0x7fffffffffffffLL;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void update(LL v, int p, int l, int r, int rt)
{
	if (l == r)
	{
		if (sum[rt] > v) sum[rt] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(v, p, l, mid, rt<<1);
	else update(v, p, mid+1, r, rt<<1|1);
	push_up(rt);
}

LL query(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r) return sum[rt];
	int mid = (l + r) >> 1;
	LL ans = 0x7fffffffffffffLL;
	if (L <= mid) ans = query(L, R, l, mid, rt<<1);
	if (R > mid) 
	{
		LL tmp = query(L, R, mid+1, r, rt<<1|1);
		ans = MIN(ans, tmp);
	}
	return ans;
}
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++) scanf("%lld", &p[i]);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		dp[0] = 0;
	//	int hh = 0, tt = 0;
		build(1, n, 1);
	//	update(p[1], a[1]>n?n:a[1], 1, n, 1);
		for (int i = 1; i <= n; i++)
		{
			LL tmp = dp[i-1] + p[i];
			int x = i + a[i] - 1;
			if (x > n) x = n;
			update(tmp, x, 1, n, 1);
			dp[i] = query(i, n, 1, n, 1);
		}
		printf("%lld\n", query(n, n, 1, n, 1));
	}
	return 0;
}
