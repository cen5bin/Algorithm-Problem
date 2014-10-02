#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20010;
int a[N], b[N];
int maxx;
int n;
int lowbit(int p)
{
	return p & (-p);
}

void plus(int *a, int x, int c)
{
	while (x <= maxx)
	{
		a[x] += c;
		x += lowbit(x);
	}
}

int sum(int *a, int x)
{
	int ret = 0;
	while (x)
	{
		ret += a[x];
		x -= lowbit(x);
	}
	return ret;
}

struct node
{
	int x, v;
}p[N];

int MAX(int a, int b)
{
	return a > b ? a : b;
}

int cmp(const node &p1, const node &p2)
{
	return p1.v > p2.v;
}
typedef long long LL;
int main()
{
	while (scanf("%d", &n) == 1)
	{
		maxx = -1;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &p[i].v, &p[i].x);
			maxx = MAX(maxx, p[i].x);
		}
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (int i = 0; i < n; i++)
		{
			plus(a, p[i].x, p[i].x);
			plus(b, p[i].x, 1);
		}
		sort(p, p+n, cmp);
		LL ans = 0;
		for (int i = 0; i < n; i++)
		{
			int tmp1 = sum(b, p[i].x-1);
			int sum1 = sum(a, p[i].x-1);
			int tmp2 = sum(b, maxx) - sum(b, p[i].x);
			int sum2 = sum(a, maxx) - sum(a, p[i].x);
			ans += ((LL)p[i].v) * (LL)(tmp1*p[i].x-sum1 + sum2 - tmp2*p[i].x);
			plus(a, p[i].x, -p[i].x);
			plus(b, p[i].x, -1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
