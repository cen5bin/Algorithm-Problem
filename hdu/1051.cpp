#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5010;
struct point
{
	int l, w;
}p[N];

bool vis[N];

int cmp(const point &p1, const point &p2)
{
	if (p1.l == p2.l) return p1.w < p2.w;
	return p1.l < p2.l;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d", &p[i].l, &p[i].w);
		sort(p, p+n, cmp);
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		for (int i = 0; i < n; i++)
		if (!vis[i])
		{
			vis[i] = 1;
			int now = p[i].w;
			int index = i;
			for (int j = i + 1; j < n; j++)
			if (!vis[j] && p[j].w >= now)
			{
				index = j;
				now = p[j].w;
				vis[j] = 1;
				cnt++;
			}
		}
		printf("%d\n", n-cnt);
	}
	return 0;
}
