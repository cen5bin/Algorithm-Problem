#include <cstdio>
#include <cstring>

typedef long long LL;

LL extend_euclid(LL a, LL b, LL &x, LL &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	LL ret = extend_euclid(b, a%b, x, y);
	LL tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ret;
}

LL reverse_element(LL n, LL mod)
{
	LL x,y;
	extend_euclid(n, mod, x, y);
	return (x % mod + mod) % mod;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) 
	{

	}
	return 0;
}
