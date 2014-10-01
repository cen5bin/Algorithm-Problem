#include <cstdio>
#include <cstring>

typedef long long LL;
const int N = 50010;
int p[N];
int a[N][12][12];

int n;
int lowbit(int p)
{
	return p & (-p);
}

void plus(int x, int c, int k, int mod)
{
	while (x <= n + 1)
	{
		a[x][k][mod] += c;
		x += lowbit(x);
	}
}

int sum(int x, int k, int mod)
{
	LL ret = 0;
	while (x)
	{
		ret += a[x][k][mod];
		x -= lowbit(x);
	}
	return ret;
}



int main()
{
	while (scanf("%d", &n) == 1)
	{
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
		int q;
		scanf("%d", &q);
		while (q--)
		{
			int c;
			scanf("%d", &c);
			if (c == 1)
			{
				int a, b, k, c;
				scanf("%d%d%d%d", &a, &b, &k, &c);
				plus(a, c, k, a % k);
				plus(b+1, -c, k, a % k);
			}
			else
			{
				int x;
				scanf("%d", &x);
				int ans = p[x];
				for (int i = 1; i <= 10; i++) ans+=sum(x, i, x % i);
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
