#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
struct node
{
	LL x, y;
}task[100010], machine[100010];

int cmp(const node &p1, const node &p2)
{
	if (p1.x == p2.x) return p1.y > p2.y;
	return p1.x > p2.x;
}

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 0; i < n; i++)
			scanf("%lld%lld", &machine[i].x, &machine[i].y);
		sort(machine, machine + n, cmp);
		for (int i = 0; i < m; i++)
			scanf("%lld%lld", &task[i].x, &task[i].y);
		sort(task, task + m, cmp);
		int count = 0;
		LL ans = 0;
		int s1 = 0;
		int s2 = 0;
		int c[110];
		memset(c, 0, sizeof(c));
		while (s2 < m)
		{
			while (s1 < n && machine[s1].x >= task[s2].x)
			{
				c[machine[s1].y]++;
				s1++;
			}
			for (int i = task[s2].y; i <=100; i++)
			if (c[i])
			{
				c[i]--;
				count++;
				ans+=500*task[s2].x+2*task[s2].y;
				break;
			}
			s2++;
		}

		printf("%d %lld\n", count, ans);
	}
	return 0;
}
