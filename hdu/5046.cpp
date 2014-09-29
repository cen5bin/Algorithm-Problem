#include <cstdio>
#include <cstring>
#include <cstdlib>

#define ABS(x) ((x)<0?(-(x)):(x))

const int SIZE = 10010;
int L[SIZE], R[SIZE], D[SIZE], U[SIZE], sz[SIZE],col[SIZE];
int col_num, cnt;

void init_dlx(int cnum)
{
	col_num = cnum;
	for (int i = 1; i <= cnum; i++)
	L[i] = i - 1, R[i-1] = i, sz[i] = 0, col[i] = i, U[i] = D[i] = i;
	L[0] = cnum, R[cnum] = 0;
	cnt = cnum + 1;	
}

void add_row(int *a, int k)
{
	int row_head = -1;
	for (int i = 0; i < k; i++)
	{
		sz[a[i]]++;
		int v = cnt++;
		col[v] = a[i];
		if (row_head == -1)
		{
			row_head = v;
			L[row_head] = R[row_head] = row_head;
		}
		else
		{
			R[v] = R[row_head];
			L[v] = row_head;
			L[R[row_head]] = v;
			R[row_head] = v;
		}
		U[v] = a[i];
		D[v] = D[a[i]];
		U[D[a[i]]] = v;
		D[a[i]] = v;
	}
}

void lr_remove(int c) { L[R[c]] = L[c]; R[L[c]] = R[c];  }
void lr_resume(int c) { R[L[c]] = L[R[c]] = c; }
void remove_col(int c)
{
	for (int i = D[c]; i != c; i = D[i])
		lr_remove(i);
}
void resume_col(int c)
{
	for (int i = U[c]; i != c; i = U[i])
		lr_resume(i);
}

int ff()
{
	bool vis[65];
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	for (int i = R[0]; i; i = R[i])
	if (!vis[i])
	{
		cnt++;
		vis[i] = 1;
		for (int j = D[i]; j != i; j = D[j])
		for (int k = R[j]; k != j; k = R[k])
			vis[col[k]] = 1;
	}
	return cnt++;
}

bool dfs(int x, int k)
{
	if (x > k) return 0;
	if (R[0] == 0) return 1;
	if (ff() + x > k) return 0;
	int mins = 0x7fffffff;
	int id = -1;
	for (int i = R[0]; i; i = R[i])
	if (sz[i] < mins)
	{
		mins = sz[i];
		id = i;
	}
	if (mins == 0) return 0;
	for (int i = D[id]; i != id; i = D[i])
	{
		remove_col(i);
		for (int j = R[i]; j != i; j = R[j])
			remove_col(j);
		if (dfs(x+1, k)) return 1;
		for (int j = L[i]; j != i; j = L[j])
			resume_col(j);
		resume_col(i);
	}
	return 0;
}
const int N = 65;
typedef long long LL;
struct point
{
	LL x, y;
}p[N];
LL cc[N][N];
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++) scanf("%lld%lld", &p[i].x, &p[i].y);
		if (n==k)
		{
			printf("Case #%d: 0\n", ++cas);
			continue;
		}
		LL mind = -1, maxd = -1;
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cc[i][j] = ABS(p[i].x-p[j].x)+ABS(p[i].y-p[j].y);
			if (mind == -1 || mind > cc[i][j]) mind = cc[i][j];
			if (maxd < cc[i][j]) maxd = cc[i][j];
		}
		while (mind < maxd)
		{
			init_dlx(n);
			LL mid = (mind + maxd) >> 1;
			for (int i = 0; i < n; i++)
			{
				int a[N], k = 0;
				for (int j = 0; j < n; j++)
				if (cc[i][j]<=mid) a[k++] = j + 1;
				add_row(a, k);	
			}
			if (dfs(0, k)) maxd = mid;
			else mind = mid + 1;
		}

		printf("Case #%d: %lld\n", ++cas, mind);
	}
	return 0;
}
