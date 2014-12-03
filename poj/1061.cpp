#include <cstdio>
#include <cstring>

typedef long long LL;
void ex_gcd(LL a, LL b, LL &d, LL &x, LL &y)
{
     if (b == 0)
     {
          x = 1;
          y = 0;
          d = a;
          return;
     }
     ex_gcd(b, a % b, d, y, x);
     y -= a / b * x;
     return;
}
#define ABS(x) (((x) < 0) ? -(x) : (x))
bool cal(LL a, LL b, LL c, LL &x, LL &y)
{
	LL d;
	ex_gcd(a, b, d, x, y);
	if (c % d) return 0;
	LL tmp = b / d;
	x = (LL)x % tmp * (c / d) % tmp;
	if (x < 0) x += (-x+ABS(tmp)-1)/ABS(tmp) * ABS(tmp);
	y = (c - a * x) / b;
	return 1;
}

int main()
{
	LL x, y, m, n, L;
	while (scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L) == 5)
	{
		LL tmp, k;
		if (!cal(m-n, L, y-x, k, tmp))
		{
			puts("Impossible");
			continue;
		}
		printf("%lld\n", k);
	}
	return 0;
}
