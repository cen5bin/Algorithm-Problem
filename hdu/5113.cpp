#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 30;
struct point
{
	int x, cnt;
}p[N],p1[N];

int cmp(const point &p1, const point &p2)
{
	return p1.cnt > p2.cnt;
}

int cc[N][N];

int move[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool judge(int x, int y, int c)
{
	for (int i = 0; i < 4; i++)
	{
		int tx = x + move[i][0];
		int ty = y + move[i][1];
		if (cc[tx][ty] == c) return 0;
	}
	return 1;
}

int n, m, k;
void print()
{
	puts("YES");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (j != 1) printf(" ");
			printf("%d", cc[i][j]);
		}
		puts("");
	}
}
bool yes;
int tx, ty, now;
void clear()
{
	memset(cc, 0, sizeof(cc));
	yes = 1;
	tx = ty = now = 1;
	for (int i = 1; i <= k; i++) p[i] = p1[i];
}

int main()
{
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= k; i++)
		{
			scanf("%d", &p1[i].cnt);
			p1[i].x = i;
		}
		sort(p1+1, p1+k+1, cmp);
		printf("Case #%d:\n", ++cas);
		clear();
		if (n * m % 2 && p[2].cnt >= n * m / 2 - 1 && p[1].cnt < (n*m+1)/2 && n > 1 && m > 1)
		{
			for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cc[i][j] = p[(i+j)%2+1].x;
			int cnt = 0, tmp[N];
			for (int i = 3; i <= k; i++)
			for (int j = 0; j < p[i].cnt; j++)
				tmp[cnt++] = p[i].x;
			if (cnt >= 1)
				cc[1][1] = tmp[0];
			if (cnt >= 2) cc[3][2] = tmp[1];
			if (cnt >= 3) cc[1][3] = tmp[2];
			print();
			continue;
		}
		if (n * m % 2 == 0 && n > 2 && m > 2 && p[2].cnt == p[1].cnt && p[2].cnt == n * m / 2 - 1)
		{
			for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cc[i][j] = p[(i+j)%2+1].x;
			int cnt = 0, tmp[N];
			for (int i = 3; i <= k; i++)
			for (int j = 0; j < p[i].cnt; j++)
				tmp[cnt++] = p[i].x;
			if (cnt >= 1)
				cc[1][1] = tmp[0];
			if (cnt >= 2) cc[3][2] = tmp[1];
			print();
			continue;
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = (i-1)%2+1; j <= m; j+=2)
			{
				cc[i][j] = p[now].x;
				if (--p[now].cnt == 0)
					now++;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = i%2+1; j <= m; j+=2)
			{
				if (!judge(i, j, p[now].x))
				{
					yes = 0;
					break;
				}
				cc[i][j] = p[now].x;
				if (--p[now].cnt == 0)
					now++;
			}
			if (!yes) break;
		}
		if (yes)
		{
			print();
			continue;
		}
		clear();
		for (int i = 1; i <= m; i++)
		{
			for (int j = (i-1)%2+1; j <= n; j+=2)
			{
				cc[j][i] = p[now].x;
				if (--p[now].cnt == 0)
					now++;
			}
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = i%2+1; j <= n; j+=2)
			{
				if (!judge(j, i, p[now].x))
				{
					yes = 0;
					break;
				}
				cc[j][i] = p[now].x;
				if (--p[now].cnt == 0)
					now++;
			}
			if (!yes) break;
		}
		if (yes)
		{
			print();
			continue;
		}
		puts("NO");
	}
	return 0;
}
