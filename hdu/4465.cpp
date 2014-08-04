#include <cstdio>
#include <cstring>
#include <cmath>

double cal(int n, double p)
{
	double q = 1 - p;
	double ret = n * p;
	double c = 1;
	for (int i = 1; i <= n; i++)
	{
		c = c * (n+i) / i * q * p;
		ret += c * (n - i);
		ret *= p;
	}
	return ret;
}

int main()
{
	int n;
	double p,q;
	int cas = 1;
	while (scanf("%d %lf", &n, &p) == 2)
	{
		printf("Case %d: %.6lf\n", cas++, cal(n, p)+cal(n,1-p) );
	}
	return 0;
}
