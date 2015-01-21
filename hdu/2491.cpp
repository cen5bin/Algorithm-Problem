#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct point 
{
	int x, y;
}p[N];

int cmp(const point &p1, const point &p2) 
{
	int t1 = (p1.y - p1.x) / 2 + 1 + p1.x;
	int t2 = (p2.y - p2.x) / 2 + 1 + p2.x;
	if (t1 == t2) return p1.x < p2.x;
	return t1 < t2;
}

int main()
{
	int n;
	while (scanf("%d", &n) && n) 
	{
		for (int i = 0; i < n; i++)
			scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p+n, cmp);
		bool yes = 1;
		int now = p[0].x;
		for (int i = 0; i < n; i++)
		{
			if (now < p[i].x) now = p[i].x;
			now += (p[i].y - p[i].x) / 2 + 1;
			if (now > p[i].y) 
			{
				yes = 0;
				break;
			}
		}
		if (yes) puts("YES");
		else puts("NO");
	}
	return 0;
}
