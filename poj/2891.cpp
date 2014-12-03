#include <cstdio>
#include <cstring>

typedef long long LL;
LL gcd(LL a, LL b)
{
	return b == 0 ? a : gcd(b, a % b);
}
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
// x 同于 r 模 m
LL ex_crt(LL *r, LL *m, int n)
{
	LL M = m[0], R = r[0], x, y, d;
	for (int i = 1; i < n; i++)
	{
		ex_gcd(M, m[i], d, x, y);
		if ((r[i]-R) % d) return -1;
		x = x * ((r[i]-R)/d) % (m[i]/d);
		R += M * x;
		M = M / d * m[i];
		R %= M;
	}
	return R > 0 ? R : R + M;
}

const int N = 1000010;
LL r[N], m[N];

int main()
{
	LL x, y;
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++)
		scanf("%lld%lld", &m[i], &r[i]);
		LL ret = ex_crt(r, m, n);
		printf("%lld\n", ret);
	}
	return 0;
}

