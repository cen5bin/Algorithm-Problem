#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
const int N = 110;
struct edge
{
	double x1, x2, h;
	edge(){}
	edge(double _x1, double _x2, double _h, int _flag):x1(_x1),x2(_x2),h(_h), flag(_flag){}
	int flag;
}e[N<<1];

double xx[N<<1];

const int M = N << 1;
int sum[M<<2], add[M<<2];
double len[M<<2];
void push_up(int l, int r, int rt)
{
	if (add[rt]) len[rt] = (xx[r+1] - xx[l]);
	else 
	len[rt] = len[rt<<1] + len[rt<<1|1];
}
void build(int l, int r, int rt)
{
	len[rt] = 0; 
	sum[rt] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void update(int v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		add[rt]+=v;
		if (add[rt]) len[rt] = xx[r+1] - xx[l];
		else if (l == r) len[rt] = 0;
		else len[rt] = len[rt<<1] + len[rt<<1|1];
		//else len[rt] = 0;
		return;
	}
//	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid ,rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(l, r, rt);
}

int cmp(const edge &e1, const edge &e2)
{
	return e1.h < e2.h;
}

int main()
{
	int n;
	int cas = 0;
	while (scanf("%d", &n) && n)
	{
		set<double> ss;
		int cnt = 0;
		for (int i = 0; i < n; i++)
		{
			double x1, x2, y1, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			ss.insert(x1);
			ss.insert(x2);
			e[cnt++] = edge(x1, x2, y1, 1);
			e[cnt++] = edge(x1, x2, y2, -1);
		}
		set<double>::iterator iter;
		int cnt1 = 0;
		map<double, int> mm;
		for (iter = ss.begin(); iter != ss.end(); iter++)
			mm[*iter] = ++cnt1, xx[cnt1] = *iter;
		sort(e, e+cnt, cmp);		
		build(1, cnt1, 1);
		double h = e[0].h;
		double ans = 0;
		for (int i = 0; i < cnt; i++)
		{
			ans += len[1] * (e[i].h - h);
			update(e[i].flag, mm[e[i].x1], mm[e[i].x2]-1, 1, cnt1, 1);
			h = e[i].h;
		}
		printf("Test case #%d\n", ++cas);
		printf("Total explored area: %.2f\n\n", ans);
	}
	return 0;
}
