#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int move[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct point
{
	int x, y, state, d;
	point(int _x, int _y):x(_x), y(_y){ d = 0; }
	point(){}
};

queue<point> q;
const int N = 110;
int f[N][N][16];

char s[N][N];
int aa[N][N];


int main()
{

	int n, m;
	while (scanf("%d%d", &n, &m)==2&&n+m)
	{
		for (int i = 0; i < n; i++) scanf("%s", s[i]);
		int k;
		scanf("%d", &k);
		memset(aa, -1, sizeof(aa));
		for (int i = 0; i < k; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x--; y--;
			aa[x][y] = i;
		}
		point start;
		bool yes = 0;
		for (int i = 0; !yes && i < n; i++)
		for (int j = 0; j < m; j++)
		if (s[i][j] == '@')
		{
			yes = 1;
			start = point(i, j);
		}
		int state = 0;
		if (aa[start.x][start.y] != -1)
			state = 1<<aa[start.x][start.y];
		memset(f, -1, sizeof(f));
		f[start.x][start.y][state] = 0;
		start.state = state;
		q.push(start);
		int ans = -1;
		while (!q.empty())
		{
			point p = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int tx = p.x + move[i][0];
				int ty = p.y + move[i][1];
				if (tx < 0 || ty < 0 || tx >= n || ty >= m || s[tx][ty] == '#') continue;
				point tmp(tx, ty);
				tmp.state = p.state;
				tmp.d = p.d + 1;
				if (aa[tx][ty] != -1) tmp.state = p.state | (1<<aa[tx][ty]);
				if (f[tx][ty][tmp.state] !=- 1 && f[tx][ty][tmp.state] <= tmp.d) continue;
				f[tx][ty][tmp.state] = tmp.d;
				q.push(tmp);
				if (tmp.state == (1<<k)-1) 
				{
					if (ans == -1 || ans > tmp.d) ans = tmp.d; 
				}
			}

		}
		printf("%d\n", ans);
	}
	return 0;
}
