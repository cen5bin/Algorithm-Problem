#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
struct point
{
	int x, y;
	point(){}
	point(int _x, int _y):x(_x), y(_y){}
	bool operator < (const point &p1) const 
	{
		if (x == p1.x) return y < p1.y;
		return x < p1.x;
	}
};

map<point, int> mm;
int move[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int N = 10010;
bool vis[N];
bool dfs(point p, int flag)
{
	vis[mm[p]] = 1;
	for (int i = 0; i < 4; i++)
	{
		int tx = p.x + move[i][0];
		int ty = p.y + move[i][1];
		if (tx < 1 || ty < 1) continue;
		point tmp = point(tx, ty);
		map<point, int>::iterator iter = mm.find(tmp);
		if (iter == mm.end()) return 0;
		if (iter->second % 2 != flag) continue;
		if (vis[iter->second]) continue;
		if (!dfs(tmp, flag)) return 0;
	}
	return 1;
}

void remove(point p, int flag)
{
	mm.erase(p);
	for (int i = 0; i < 4; i++)
	{
		int tx = p.x + move[i][0];
		int ty = p.y + move[i][1];
		if (tx < 1 || ty < 1) continue;
		point tmp = point(tx, ty);
		map<point, int>:: iterator iter = mm.find(tmp);
		if (iter == mm.end()) continue;
		if (iter->second % 2 != flag) continue;
		remove(tmp, flag);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		mm.clear();
		int n;
		scanf("%d", &n);
		int cnt = 0;
		int flag = 0;
		while (n--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			point pp = point(x, y);
			mm[pp] = cnt++;
			for (int i = 0; i < 4; i++)
			{
				int tx = x + move[i][0];
				int ty = y + move[i][1];
				if (tx < 1 || ty < 1) continue;
				point tmp = point(tx, ty);
				map<point, int>::iterator iter = mm.find(tmp);
				if (iter == mm.end() || iter->second % 2 == flag) continue;
				//if (vis[iter->second]) continue;
				memset(vis, 0, sizeof(vis));
				if (dfs(tmp, 1 - flag))
					remove(tmp, 1-flag);
			}
			if (dfs(pp, flag)) remove(pp, flag);
			flag = 1 - flag;
		}
		map<point, int>::iterator iter;
		int ans[2] = {0, 0};
		for (iter = mm.begin(); iter != mm.end(); iter++)
		ans[iter->second % 2]++;
		printf("%d %d\n", ans[0], ans[1]);
	}
	return 0;
}
