#include <cstdio>
#include <cstring>
const int N = 100010;
int a[N<<1];

int hh, tt;
int q[N<<1], id[N<<1];
int MAX(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	int cc;
	scanf("%d", &cc);
	while (cc--)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			a[n+i] = a[i];
		}
		a[0] = 0;
		for (int i = 1; i < 2 * n; i++) a[i] += a[i-1];
		tt = hh = 0;
		int ans = a[1];
		q[tt] = 0;
		id[tt++] = 0;
		int start = 1, end = 1;
		for (int i = 1; i < 2 * n; i++)
		{
			if (ans < a[i] - q[hh])
			{
				start = id[hh] + 1;
				end = i;
				ans = a[i] - q[hh];
			}
			while (hh < tt && id[hh] <= i - k) hh++;
			while (hh < tt && a[i] < q[tt-1]) tt--;
			q[tt] = a[i];
			id[tt++] = i;
		}
		if (start > n) start-= n;
		if (end > n) end -= n;
		printf("%d %d %d\n", ans, start, end);
	}
	return 0;
}
