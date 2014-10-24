#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;
map<LL, LL> mm;

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
struct node
{
	LL index, val;
}pp[N];
int cmp(const node &p1, const node &p2)
{
	if (p1.val == p2.val) return p1.index < p2.index;
	return p1.val < p2.val;
}

LL find(LL x, LL m)
{
	LL low = 0, high = m;
	while (low < high)
	{
		LL mid = (low + high) >> 1;
		if (pp[mid].val < x) low = mid + 1;
		else if (pp[mid].val > x) high = mid - 1;
		else high = mid;
		
	}
	if (pp[low].val == x) return pp[low].index;
	return -1;
}
int main()
{
	LL p, a, b;
	while (scanf("%lld%lld%lld", &p, &a, &b) == 3)
	{
		LL a0 = exp_mod(a, p-2, p);
		LL m = (int)sqrt(p)+1;
		LL tmp = 1;
		pp[0].val = b % p;
		pp[0].index = 0;
		for (int i = 1; i <= m; i++)
		{
			tmp = tmp * a0 % p;
			pp[i].val = tmp * b % p;
			pp[i].index = i;
		}
		sort(pp, pp+m+1, cmp);
		LL aa = exp_mod(a, m, p);
		LL ans = -1;
		 tmp = 1;
		for (int i = 0; i <= p / m; i++)
		{
			LL xx = find(tmp, m);
			if (xx != -1)
			//if (mm.find(tmp) != mm.end())
			{
				ans = i * m + xx;
				break;
			}
			tmp = tmp * aa % p;
		}
		if (ans == -1)
			puts("no solution");
		else printf("%lld\n", ans);

	}
	return 0;
}
