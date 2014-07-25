#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

#define MOD 1000000007

//扩展euclid算法,ax+by=gcd(a,b)
LL extend_euclid(LL a, LL b, LL &x, LL &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	LL res = extend_euclid(b, a % b, x, y);
	LL tmp = x;
	x = y;
	y = tmp - a / b * y;
	return res;	
}

//逆元 返回值为n对于模mod的逆元
LL inverse_element(LL n, LL mod)
{
	LL x,y;
	extend_euclid(n, mod, x, y);
	return (x % mod + mod) % mod;
}

//组合数计算, C(m,n) 模 mod的结果
LL C(LL m, LL n, LL mod)
{
	LL ans = 1;
	for (LL i = m; i >= m - n + 1; i--)
		ans = ans * (i%mod) % mod * inverse_element(m-i+1, mod) % mod;
	return ans;
}

int main()
{
	int n;
	LL s;
	LL a[25];
	while (cin>>n>>s)
	{
		for (int i = 0; i < n; i++)
			cin >> a[i];
		LL sum = 0;
		for (int i = 0; i < n; i++)
			sum += a[i];
		LL ans = 0;
		for (int i = 0; i < (1<<n); i++)
		{
			LL tmp = s;
			LL flag = 1;
			for (int j = 0; j < n; j++)
				if (i & (1<<j))
				{
					tmp-=a[j]+1;
					flag *= -1;
				}
			if (tmp < 0) continue;
			ans += C(tmp+n-1, n-1, MOD) * flag;
			ans %= MOD;
		}
		cout << (ans%MOD+MOD)%MOD << "\n";
	}
	return 0;
}
