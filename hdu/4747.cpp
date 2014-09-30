#include <cstdio>
#include <cstring>
//#include <set>
#include <map>
using namespace std;

//set<LL> ss;
typedef long long LL;
const int N = 200010;
LL MAX(LL a, LL b)
{
	return  a > b ? a : b;
}
map<LL, int> mm;
LL mex[N];
LL nxt[N];
LL a[N];
LL sum[N<<2], flag[N<<2], maxx[N<<2];
int cnt;
void push_up(int rt)
{
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
	if (flag[rt<<1] != flag[rt<<1|1]) flag[rt] = -1;
	else flag[rt] = flag[rt<<1];
	maxx[rt] = MAX(maxx[rt<<1], maxx[rt<<1|1]);
}
void push_down(int l, int r, int rt)
{
	if (flag[rt] == -1) return;
	flag[rt<<1] = flag[rt<<1|1] = flag[rt];
	int mid = (l + r) >> 1;
	sum[rt<<1] = flag[rt<<1] * (mid - l + 1);
	sum[rt<<1|1] = flag[rt<<1|1] * (r - mid);
	maxx[rt<<1] = maxx[rt<<1|1] = maxx[rt];
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		flag[rt] = maxx[rt] = sum[rt] = mex[cnt++];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(rt);
}

void update(LL v, int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
	{
		sum[rt] = v * (LL)(r - l + 1);
		maxx[rt] = flag[rt] = v;
		return;
	}
	push_down(l, r, rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(v, L, R, l, mid, rt<<1);
	if (R > mid) update(v, L, R, mid+1, r, rt<<1|1);
	push_up(rt);
}

LL query(int L, int R, int l, int r, int rt)
{
	if (L <= l && R >= r)
		return sum[rt];
	push_down(l, r, rt);
	int mid = (l + r) >> 1;
	LL ans = 0;
	if (L <= mid) ans = query(L, R, l, mid, rt<<1);
	if (R > mid) ans += query(L, R, mid+1, r, rt<<1|1);
	push_up(rt);
	return ans;
}

int query(int v, int L, int R, int l, int r, int rt)
{
	if (maxx[rt] <= v) return -1;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (L <= mid && maxx[rt<<1] > v) return query(v, L, R, l, mid, rt<<1);
	return query(v, L, R, mid+1, r, rt<<1|1);
}

int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		//ss.clear();
		mm.clear();
		LL mex0 = 0;
		for (int i = 1; i <= n; i++)
		{
			if (mm.find(a[i]) != mm.end()) nxt[mm[a[i]]] = i;
			nxt[i] = n + 1;
			if (a[i] != mex0) mex[i] = mex0;
			else
			{
				mex0++;
				while (mm.find(mex0) != mm.end()) mex0++;
				mex[i] = mex0;
			}
			mm[a[i]] = i;
		}
		cnt = 1;
		build(1, n, 1);
		LL ans = 0;
		for (int i = 1; i <= n; i++)
		{
			ans += query(i, n, 1, n, 1);
			int tmp = query(a[i], i+1, nxt[i]-1, 1, n, 1);
			if (tmp != -1)
			update(a[i], tmp, nxt[i]-1, 1, n, 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
