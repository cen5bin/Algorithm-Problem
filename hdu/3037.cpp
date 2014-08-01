#include <cstdio>
#include <cstring>

typedef long long LL;

LL fac[100010];  //n! % p的结果

void init(LL p)
{
	fac[0] = 1;
	for (int i = 1; i <= p; i++)
		fac[i] = fac[i-1] * i % p;
}

LL exp_mod(LL a, LL b, LL c)
{
	LL ans = 1;
	a %= c;
	while (b)
	{
		if (b&1)
			ans = ans * a % c;
		a = a * a % c;
		b>>=1;
	}
	return ans;
}

//组合数计算, C(n,m) 模 mod的结果
LL C(LL n, LL m, LL mod)
{
	if (m > n) return 0;
	return fac[n] * exp_mod(fac[n-m]*fac[m]%mod, mod-2, mod) % mod;
}

LL lucas(LL n, LL m, LL mod)
{
	if (m==0) return 1;
	LL tmp = C(n % mod, m % mod, mod);
	if (tmp == 0) return 0;
	return tmp * lucas(n/mod, m/mod, mod) % mod;
}


int main()
{
	
	int t;
	scanf("%d", &t);
	while (t--)
	{
		LL m,n,p;
		scanf("%lld%lld%lld", &n, &m, &p);
		init(p);
		printf("%lld\n", lucas(m+n, n, p));
	}
	return 0;
}