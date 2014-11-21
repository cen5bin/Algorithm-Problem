#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3010;
int a[N];

struct point
{
	int id, val;
}p[N];

int cmp(const point &p1, const point &p2)
{
	if (p1.val == p2.val) return p1.id < p2.id;
	return p1.val < p2.val;
}

int ans[N][2];
int cnt;
void swap(int &a, int &b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		
		cnt = 0;
		for (int i = 0; i < n; i++)
		{
			int minx = 0x7fffffff, id = 0;
			for (int j = i; j < n; j++)
			if (a[j] < minx)
			{
				minx = a[j];
				id = j;
			}
			if (id == i) continue;
			ans[cnt][0] = i;
			ans[cnt++][1] = id;
			swap(a[i], a[id]);
		}

		printf("%d\n", cnt);
		for (int i = 0; i < cnt; i++)
		printf("%d %d\n", ans[i][0], ans[i][1]);
	}
}
