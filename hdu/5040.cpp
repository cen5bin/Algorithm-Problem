#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
//#define abs(x) ((x)<0?(-(x)):(x))
using namespace std;
const int N = 510;
char s[N][N];
struct point
{
	int x, y, inbox, wait, tt;
};
//queue<point> q;

int move0[4][2] = {{-1,0}, {0, 1},{1,0},{0,-1}};
int c[4][N][N];
int direction(char c)
{
	if (c == 'N') return 0;
	if (c == 'E') return 1;
	if (c == 'S') return 2;
	if (c == 'W') return 3;
	return -1;
}
int f[N][N][2][4];
point qq[500 * 500 * 4 * 12 + 10];
int hh, tt;
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%s", s[i]+1);
		point p;
		point ee;
		bool find = 0;
		for (int i = 1; !find && i <= n; i++)
		for (int j = 1; j <= n; j++)
		if (s[i][j] == 'M')
		{
			p.x = i;
			p.y = j;
			find = 1;
			//break;
		}
		else if (s[i][j] == 'T')
		{
			ee.x = i;
			ee.y = j;
		}
		memset(c, -1, sizeof(c));
		int d;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		for (int k = 0; k < 4; k++)
		if ((d=direction(s[i][j]))!=-1)
		{
			d = (d+k)%4;
			int tx = i + move0[d][0];
			int ty = j + move0[d][1];
			c[k][i][j] = 1;
			if (tx < 1 || ty < 1 || tx > n || ty > n)
				continue;
			c[k][tx][ty] = 1;
		}
		else if(s[i][j] == '#')
			c[k][i][j] = -1;
		else if (s[i][j] == '.' || s[i][j] == 'M') 
		{
			if (c[k][i][j] != 1)
			c[k][i][j] = 0;
		}
		else 
		{
			if (c[k][i][j] != 1)
				c[k][i][j] = 2;
		}
		tt = hh = 0;
		p.wait = p.tt = 0;
		p.inbox = 0;
		memset(f, -1, sizeof(f));
		f[p.x][p.y][0][0] = 0;
		qq[tt++] = p;
		int ans = 0x7fffffff;
		find = 0;
		while (hh < tt)
		{
			point p0 = qq[hh++];
			if (p0.tt >= ans - 1) continue;
			if (f[p0.x][p0.y][0][p0.wait] != -1 && f[p0.x][p0.y][0][p0.wait] < p0.tt) continue;
			for (int j = 0; j < 2; j++)
			{
				if (j==0 && c[p0.tt & 3][p0.x][p0.y] == 1) continue;
				for (int i = 0; i < 4; i++)
				{
					int tx = p0.x + move0[i][0];
					int ty = p0.y + move0[i][1];
					if (tx < 1 || ty < 1 || tx > n || ty > n || s[tx][ty] == '#') continue;
					if (j==0 && c[p0.tt & 3][tx][ty] == 1) continue;
//					if (j==1 && c[p0.tt & 3][tx][ty] != 1) continue;
					point tmp = p0;
					tmp.x = tx, tmp.y = ty;
					tmp.tt = p0.tt + (j==0?1:3);
					tmp.wait = 0;
					if (f[tx][ty][0][0] != -1 && f[tx][ty][0][0] <= tmp.tt) continue;
					if (tmp.tt >= ans) continue;
					if (s[tx][ty] == 'T')
					{
						if (tmp.tt < ans) 
						ans = tmp.tt;
						find = 1;
						continue;
					}
					qq[tt++] = tmp;
					f[tx][ty][0][0] = tmp.tt;
				}
			}
				if (p0.wait == 3) continue;
				p0.wait++;
				p0.tt++;
				if (f[p0.x][p0.y][0][p0.wait] != -1 && f[p0.x][p0.y][0][p0.wait] <= p0.tt) continue;
				qq[tt++] = p0;
				f[p0.x][p0.y][0][p0.wait] = p0.tt;
		}

		printf("Case #%d: ", ++cas);
		if (find) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
}
