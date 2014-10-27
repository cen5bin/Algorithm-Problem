#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
LL exp_mod(LL a, LL b, LL c)
{
	LL ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % c;
		a = a * a % c;
		b >>= 1;
	}
	return ret;
}

const int N = 100010;
LL prime[N];
bool check[N];
int cnt;
void getPrime()
{
	cnt = 0;
	memset(check, 0, sizeof(check));
	for (int i = 2; i < N; i++)
	{
		if (!check[i]) prime[cnt++] = i;
		for (int j = 0; j < cnt; j++)
		{
			if (prime[j] * i >= N) break;
			check[prime[j] * i] = 1;
		}
	}
}

LL phi(LL x)
{
	LL ret = x;
	for (int i = 0; i < cnt && prime[i] * prime[i] <= x; i++)
	if (x % prime[i] == 0)
	{
		ret = ret / prime[i] * (prime[i] - 1);
		while (x % prime[i] == 0) x /= prime[i];
	}
	if (x > 1) ret = ret / x * (x-1);
	return ret;
}

LL gcd(LL a, LL b)
{
	return b == 0 ? a : gcd(b, a % b);
}

struct node
{
	LL val;
	int index;
}p[N];
int cmp(const node &p1, const node &p2)
{
	if (p1.val == p2.val) return p1.index < p2.index;
	return p1.val < p2.val;
}
LL find(LL x, LL m)
{
	LL low = 0, high = m-1;
	while (low < high)
	{
		LL mid = (low + high) >> 1;
		if (p[mid].val < x) low = mid + 1;
		else if (p[mid].val > x) high = mid - 1;
		else high = mid;
	}
	if (p[low].val == x) return p[low].index;
	return -1;
}
LL work(LL a, LL b, LL c)
{
	a %= c;
	b %= c;
	LL tmp = 1 % c;
	for (int i = 0; i < 50; i++)
	{
		if (tmp == b) return i;
		tmp = tmp * a % c;
	}
	if (c < 50) return -1;
	tmp = 1;
	LL d;
	int cnt = 0;
	while ((d=gcd(a, c)) != 1)
	{
		if (b % d) return -1;
		tmp = tmp * (a / d) % c;
		cnt++;
		c /= d;
		b /= d;
	}
	if (gcd(b, c) != 1) return -1;
	b = b * exp_mod(tmp, phi(c)-1, c) % c;
	LL m = ceil(sqrt(c*1.0)) + 1;
	LL na = exp_mod(a, phi(c)-1, c);
	p[0].val = b;
	p[0].index = 0;
	for (int i = 1; i < m; i++)
	{
		p[i].val = p[i-1].val * na % c;
		p[i].index = i;
	}
	sort(p, p+m, cmp);
	LL am = exp_mod(a, m, c);
	tmp = 1;
	for (int i = 0; i < m; i++)
	{
		LL ret = find(tmp, m);
		if (ret != -1)
			return cnt + i * m + ret;
		tmp = tmp * am % c;
	}
	return -1;
}


int main()
{
	//printf("%lld", exp_mod(3LL, 51LL, 143243LL));
	getPrime();
	//for (int i = 0; i < 10; i++) printf("%lld ", prime[i]);
	LL a, b, c;
	while (scanf("%lld%lld%lld", &a, &c, &b) == 3 && a + b + c)
	{
		LL ret = work(a, b, c);
		if (ret == -1)
			puts("No Solution");
		else printf("%lld\n", ret);
	}
	return 0;
}
