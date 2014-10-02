#include <cstdio>
#include <cstring>
const int N = 5010;
int x[N];
int a[N];
int n;
int lowbit(int p)
{
	return p & (-p);
}

void plus(int x, int c)
{
	while (x <= n)
	{
		a[x] += c;
		x += lowbit(x);
	}
}

int sum(int x)
{
	int ret = 0;
	while (x)
	{
		ret += a[x];
		x -= lowbit(x);
	}
	return ret;
}

int MIN(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	while (scanf("%d", &n) ==1)
	{
		memset(a, 0, sizeof(a));
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &x[i]);
			x[i]++;
			ans += sum(n) - sum(x[i]);
			plus(x[i], 1);
		}
		int tmp = ans;
		for (int i = 0; i < n; i++)
		{
			tmp = tmp - sum(x[i]-1) + sum(n) - sum(x[i]);
			ans = MIN(ans, tmp);
		//	plus([i])

		}
		printf("%d\n", ans);
	}
	return 0;
}
