#include <cstdio>
#include <cstring>

const int N = 200010;
int p[N];
int a[N], b[N];
void init_kmp(int *a, int n)
{
	p[0] = -1;
	p[1] = 0;
	int j = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j != -1 && a[i] != a[j+1]) j = p[j];
		p[i] = ++j;
	}
}

int match(int *a, int n1, int *b, int n2)
{
	int ret = 0;
	int j = 0;
	for (int i = 1; i <= n1; i++)
	{
		while (j != -1 && a[i] != b[j+1]) j = p[j];
		j++;
		if (j == n2)
		{
			j = p[j];
			ret++;
		}
	}
	return ret;
}

int main()
{
	int n, w;
	scanf("%d%d", &n, &w);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) a[i] -= a[i+1];
	n--;
	for (int i = 1; i <= w; i++) scanf("%d", &b[i]);
	for (int i = 1; i < w; i++) b[i] -= b[i+1];
	w--;
	if (w == 0)
	{
		printf("%d\n", n+1);
		return 0;
	}
	init_kmp(b, w);
	printf("%d\n", match(a, n, b, w));
	return 0;
}
