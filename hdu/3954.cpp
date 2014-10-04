#include <cstdio>
#include <cstring>

const int N = 10010;
int kk[15], k;
int sum[N<<2][12], e[N<<2];

inline int MAX(int a, int b)
{
	return a > b ? a : b;
}

bool level_up(int rt, int v)
{
	bool yes = 0;
	for (int i = 1; i <= k; i++)
	if (sum[rt][i])	
	{
		sum[rt][i] += i * v;
		yes = 1;
	}
	if (!yes) sum[rt][1] += v;
	bool ret = 0;
	for (int i = k - 1; i > 0; i--)
	for (int j = k; j >= i + 1; j--)
	if (sum[rt][i] >= kk[j])
	{
		if (sum[rt][i] > sum[rt][j]) sum[rt][j] = sum[rt][i];
		sum[rt][i] = 0;
		ret = 1;
	}
	return ret;
}

void push_up(int rt)
{
	for (int i = 1; i <= k; i++)
		sum[rt][i] = MAX(sum[rt<<1][i], sum[rt<<1|1][i]);
}
void push_down(int l, int r, int rt)
{
	if (e[rt] == 0) return;
	if (l == r) return;
	e[rt<<1] += e[rt];
	e[rt<<1|1] += e[rt];
	int mid = (l + r) >> 1;
	if (level_up(rt<<1, e[rt])) push_down(l, mid, rt<<1);
	if (level_up(rt<<1|1, e[rt])) push_down(mid+1, r, rt<<1|1);
	e[rt] = 0;
	push_up(rt);
}


void build(int l, int r, int rt)
{
	for (int i = 1; i <= k; i++) sum[rt][i] = 0;
	e[rt] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		e[rt] += v;
		if (level_up(rt, v)) push_down(l, r, rt);
//		if (l != r)
//		push_up(rt);
		return;
	}
	push_down(l, r, rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		for (int i = k; i > 0; i--)
		if (sum[rt][i]) return sum[rt][i];
		return 0;
	}
	push_down(l, r, rt);
	int mid = (l + r) >> 1;
	int ans = 0;
	if (L <= mid) ans = query(L, R, l, mid, rt<<1);
	if (R > mid) ans = MAX(ans, query(L, R, mid+1, r, rt<<1|1));
//	push_up(rt);
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		int n, q;
		scanf("%d%d%d", &n, &k, &q);
		for (int i = 2; i <= k; i++) scanf("%d", &kk[i]);
		build(1, n, 1);
		printf("Case %d:\n", ++cas);
		while (q--)
		{
			char c;
			int x, y, z;
			scanf(" %c", &c);
			if (c == 'W')
			{
				scanf("%d%d%d", &x, &y, &z);
				update(z, x, y, 1, n, 1);
			}
			else 
			{
				scanf("%d%d", &x, &y);
				printf("%d\n", query(x, y, 1, n, 1));
			}
		}
		puts("");
	}
	return 0;
}
