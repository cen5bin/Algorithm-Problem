#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 15010;
struct point
{
	int x, y;
}p[N];
int cmp(const point &p1, const point &p2)
{
	if (p1.y == p2.y) return p1.x < p2.x;
	return p1.y < p2.y;
}

int a[32010];
int maxx;
int lowbit(int p)
{
	return p & (-p);
}
void plus(int x, int c)
{
	while (x <= maxx)
	{
		a[x] += c;
		x += lowbit(x);
	}
}
int sum(int x)
{
	int ret = 0;
	while (x)
	{
		ret += a[x];
		x -= lowbit(x);
	}
	return ret;
}
int ans[N];
int MAX(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		//maxx = 0;
		for (int i = 0; i < n; i++) 
		{
			scanf("%d%d", &p[i].x, &p[i].y);
			p[i].x++;
			maxx = MAX(maxx, p[i].x);
		}
	//	maxx = p[n-1].x;
//		sort(p, p+n, cmp);
		memset(a, 0, sizeof(a));
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; i++)
		{
			ans[sum(p[i].x)]++;
			plus(p[i].x, 1);
		}
		for (int i = 0; i < n; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
