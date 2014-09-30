#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;
map<LL, int> mm;
set<LL> ss;
const int N = 100010;
LL sum[N<<2][5];
int cnt[N<<2];
void push_up(int rt)
{
	cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
	for (int i = 0; i < 5; i++)
		sum[rt][i] = sum[rt<<1][i] + sum[rt<<1|1][(5-cnt[rt<<1]%5+i)%5];
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		for (int i = 0; i < 5; i++) sum[rt][i] = 0;
		cnt[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(rt);
}
void update(int p, LL v, int l, int r, int rt)
{
	if (l == r)
	{
		for (int i = 0; i < 5; i++) sum[rt][i] = 0;
		if (v) sum[rt][1] = v, cnt[rt] = 1;
		//if (v) cnt[rt] = 1;
		else cnt[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(p, v, l, mid, rt<<1);
	else update(p, v, mid+1, r, rt<<1|1);
	push_up(rt);
}

char s[10];
LL xx[N];
int op[N];
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		mm.clear();
		ss.clear();
		memset(cnt, 0, sizeof(cnt));
		memset(sum, 0, sizeof(sum));
		build(1, n, 1);
		int id = 1;
		int cnt0 = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s);
			if(s[0] == 'a')
			{
				op[i] = 1;
				scanf("%lld", &xx[i]);
				ss.insert(xx[i]);
			}
			else if (s[0] == 'd')
			{
				op[i] = -1;
				scanf("%lld", &xx[i]);
			}
			else op[i] = 0;
		}
		set<LL>::iterator iter;
		for (iter = ss.begin(); iter != ss.end(); iter++)
			mm[*iter] = id++;
		for (int i = 0; i < n; i++)
		{
			if (op[i] == 0) printf("%lld\n", sum[1][3]);
			else if (op[i] == 1) update(mm[xx[i]], xx[i], 1, n, 1);
			else update(mm[xx[i]], 0, 1, n, 1);
		}
	}

	return 0;
}
