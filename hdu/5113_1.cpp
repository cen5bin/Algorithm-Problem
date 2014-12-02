#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, k;
const int N = 6;
int cc[N][N];
struct point
{
	int x, cnt;
}p[N * N];
int move[2][2] = {{-1, 0}, {0, -1}};
//int move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool judge(int x, int y, int c)
{
	for (int i = 0; i < 2; i++)
	{
		int tx = x + move[i][0];
		int ty = y + move[i][1];
		if (cc[tx][ty] == c) return 0;
	}
	return 1;
}
int cmp(const point &p1, const point &p2)
{
	return p1.cnt > p2.cnt;
}
bool dfs(int x)
{
	if (x == n * m) return 1;
	for (int i = 1; i <= k; i++)
	if ((n * m - x + 1) / 2 < p[i].cnt) return 0;
	int tx = x / m + 1;
	int ty = (x)%m+1;
	for (int i = 1; i <= k; i++)
	if (p[i].cnt && judge(tx, ty, p[i].x))
	{
		p[i].cnt--;
		cc[tx][ty] = p[i].x;
		if (dfs(x+1)) return 1;
		cc[tx][ty] = 0;
		p[i].cnt++;
	}
	return 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		bool yes = 1;		
		for (int i = 1; i <= k; i++) 
		{
			scanf("%d", &p[i].cnt);
			p[i].x = i;
			if (p[i].cnt > (n * m + 1) / 2) yes = 0;
		}
		printf("Case #%d:\n", ++cas);
		if (!yes)
		{
			puts("NO");
			continue;
		}
		memset(cc, 0, sizeof(cc));
		sort(p+1, p + k + 1, cmp);
		if (!dfs(0))
		{
			puts("NO");
			continue;
		}
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
	return 0;
}
