#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int N = 210;
char s[N][N];

const int M = 20;
struct point 
{
	int x, y;
	point(){}
	point(int _x, int _y):x(_x), y(_y){}
	bool operator < (const point &p) const 
	{
		if (x == p.x) return y < p.y;
		return x < p.x;
	}
}p[M];

map<point, int> mm;
int move[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool vis[M];

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && (n+m))
	{
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		int cnt = 0;
		mm.clear();
		for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (s[i][j] == '.')
			{
				p[cnt] = point(i, j);
				mm[p[cnt]] = cnt++;
			}
		if (cnt == 0)
		{
			puts("0");
			continue;
		}
		int ans = cnt+1;
		for (int i = 1; i < (1<<cnt); i++)
		{
			int room[M];
			int k = i, tmp = 0, cnt0 = 0;
			while (k)
			{
				if (k & 1)
					room[cnt0++] = tmp;
				k >>= 1;
				tmp++;
			}
			if (cnt0 >= ans) continue;
			for (int j = 0; j < cnt0; j++)
			for (int k = 0; k < 4; k++)
			{
				point special = p[room[j]];
				int tx = special.x + move[k][0];
				int ty = special.y + move[k][1];
				if (tx >= 0 && tx < n && ty >= 0 && ty < m && s[tx][ty] == '#') continue;
				memset(vis, 0, sizeof(vis));
				if (tx >= 0 && tx < n && ty >= 0 && ty < m)
				vis[mm[point(tx, ty)]] = 1;
				tx = special.x + move[(k+1) % 4][0];
				ty = special.y + move[(k+1) % 4][1];
				if (tx >= 0 && tx < n && ty >= 0 && ty < m && s[tx][ty] == '#') continue;
				if (tx >= 0 && tx < n && ty >= 0 && ty < m)
					vis[mm[point(tx, ty)]] = 1;
				vis[mm[special]] = 1;
				bool fail = 0;
				for (int l = 0; l < cnt0; l++)
				if (l != j)
				{
					point tmp = p[room[l]];
					int tx = tmp.x + move[0][0];
					int ty = tmp.y + move[0][1];
					if (tx >= 0 && tx < n && ty >= 0 && ty < m && s[tx][ty] == '#') 
					{
						fail = 1;
						break;
					}
					if (tx >= 0 && tx < n && ty >= 0 && ty < m)
					vis[mm[point(tx, ty)]] = 1;
					tx = tmp.x + move[1][0];
					ty = tmp.y + move[1][1];
					if (tx >= 0 && tx < n && ty >= 0 && ty < m && s[tx][ty] == '#') 
					{
						fail = 1;
						break;
					}
					if (tx >= 0 && tx < n && ty >= 0 && ty < m)
					vis[mm[point(tx, ty)]] = 1;
					vis[mm[tmp]] = 1;
				}
				if (fail) continue;
				for (int l = 0; !fail && l < cnt; l++)
					if (!vis[l]) fail = 1;
				if (fail) continue;
				ans = MIN(ans, cnt0);
//				printf("%d %d %d\n", k, special.x, special.y);
			}
		}
		if (ans > cnt) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;
}
