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

LL inverse_element(LL a, LL m)
{
	LL d, x, y;
	ex_gcd(a, m, d, x, y);
	return (x % m + m) % m;
}

LL inverse_element1(LL a, LL m)
{
	return exp_mod(a, m-2, m);
}

LL cal(LL a, LL b, LL c)
{
	return a % (b * c) / b; 
}
int main()
{
	//printf("%lld\n", cal(188, 2, 10));
	LL a, b;
	while (scanf("%lld%lld", &a, &b) == 2)
	{
		//printf("%lld\n", inverse_element(a, b));
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
			ans = ans * cal((exp_mod(tt, cnt*b+1, MOD*(tt-1))-1), tt-1, MOD) % MOD;//  * inverse_element(tt-1, MOD) % MOD;
		}
		if (a > 1)
		{
			LL tt = a % MOD;
			if (tt == 1)
				ans = ans * (b + 1) % MOD;
			else if (tt)
				ans = ans * cal((exp_mod(tt, b+1, MOD*(tt-1))-1), tt-1, MOD) % MOD;//  * inverse_element(tt-1, MOD) % MOD;
				//ans = ans * (exp_mod(tt, b+1, MOD)-1) % MOD * inverse_element(tt-1, MOD) % MOD;
		}
		printf("%lld\n", (ans+MOD) % MOD);
	}
	return 0;
}
