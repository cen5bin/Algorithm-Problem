#include <cstdio>
#include <cstring>
typedef long long LL;
const LL MOD = 9901;

LL exp_mod(LL a, LL b, LL c)
{
	LL ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % c;
		a = a * a % c;
		b >>= 1;
	}
	return ret;
}

LL inverse_element(LL a, LL m)
{
	return exp_mod(a, m-2, m);
}

int main()
{
	LL a, b;
	while (scanf("%lld%lld", &a, &b) == 2)
	{
		if (a == 0 || b == 0)
		{
			puts("1");
			continue;
		}
		LL ans = 1;
		for (LL i = 2; i * i <= a; i++)
		if (a % i == 0)
		{
			LL cnt = 0;
			while (a % i == 0) a /= i, cnt++;
			LL tt = i % MOD;
			if (tt == 0) continue;
			if (tt == 1)
			{
				ans = ans * (b * cnt % MOD + 1) % MOD;
				continue;
			}
			ans = ans * (exp_mod(tt, cnt*b+1, MOD)-1) % MOD * inverse_element(tt-1, MOD) % MOD;
		}
		if (a > 1)
		{
			LL tt = a % MOD;
			if (tt == 1)
				ans = ans * (b + 1) % MOD;
			else if (tt)
				ans = ans * (exp_mod(tt, b+1, MOD)-1) % MOD * inverse_element(tt-1, MOD) % MOD;
		}
		printf("%lld\n", (ans+MOD) % MOD);
	}
	return 0;
}
