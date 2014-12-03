#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int SIZE = 10010;
#define inf 0x7fffffff
bool vis[SIZE];
int xx[SIZE];
int cc[55];
struct DLX
{
	int L[SIZE], R[SIZE], U[SIZE], D[SIZE];
	int sz[SIZE]; // 表示每个列中1的个数
	int col[SIZE], row[SIZE];
	int col_num, cnt, row_num;
	int ans;
	void init(int cnum)
	{
		col_num = cnum;
		for (int i = 1; i <= cnum; i++)
			L[i] = i - 1, R[i-1] = i, U[i] = D[i] = i, col[i] = i, sz[i] = 0;
		L[0] = cnum;
		R[cnum] = 0;
		cnt = cnum + 1;
		row_num = 0;
		ans = inf;
	}
	// a中存的数字表示有1的列
	void addrow(vector<int> a)
	{
		row_num++;
		int row_head = -1;
		for (int i = 0; i < a.size(); i++)
		{
			sz[a[i]]++;
			int v = cnt++;
			col[v] = a[i];
			row[v] = row_num;
			if (row_head == -1)
			{
				//表示该行还没有头节点，因此当前这个节点要变成头节点
				row_head = v;
				L[v] = R[v] = v;
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
	void remove_col(int c) //删除第c列
	{
		 for (int i = D[c]; i != c; i = D[i]) lr_remove(i);
	}
	void resume_col(int c) //恢复第c列
	{
		 for (int i = U[c]; i != c; i = U[i]) lr_resume(i);
	}
	int h()
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
		 return cnt;
	}
	void dfs(int k)
	{
		if (R[0] == 0) 
		{
			if (ans > k) ans = k;
			return;
		}
		if (h() + k >= ans) return;
		int minx = inf, id = 0;
		for (int i = R[0]; i; i = R[i])
		if (sz[i] < minx)
		{
			minx = sz[i];
			id = i;
		}
		if (minx == 0) return;
		for (int i = D[id]; i != id; i = D[i])
		{
			if (vis[row[i]]) continue;
			remove_col(i);
			vis[row[i]] = vis[xx[row[i]]] = 1;
			for (int j = R[i]; j != i; j = R[j])
				remove_col(j);
			dfs(k+1);
			vis[row[i]] = vis[xx[row[i]]] = 0;
			for (int j = L[i]; j != i; j = L[j])
				resume_col(j);
			resume_col(i);
		}
	}
	void clear0()
	{
		for (int i = R[0]; i; i = R[i])
			if (sz[i] == 0) 
			{
				remove_col(i);
				lr_remove(i);
			}
	}
}dlx;

vector<int> a0;
int main()
{
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T--)
	{
		int n;
		scanf("%d", &n);
		memset(cc, 0, sizeof(cc));
		dlx.init(n * 2);
		memset(xx, 0, sizeof(xx));
		for (int i = 0; i < n; i++)
		{
			int m;
			scanf("%d", &m);
			for (int j = 0; j < m; j++)
			{
				a0.clear();
				int k;
				scanf("%d", &k);
				a0.push_back(i*2+j+1);
				if (m == 2)
					a0.push_back(i*2+1-j+1);
				while (k--)
				{
					int x, y;
					scanf("%d%d", &x, &y);
					a0.push_back(x*2+y+1);		
				}
				dlx.addrow(a0);
			}
			if (m == 2)
				xx[dlx.row_num] = dlx.row_num-1, xx[dlx.row_num-1] = dlx.row_num;
		}
		memset(vis, 0, sizeof(vis));
		dlx.clear0();
		dlx.dfs(0);
		printf("Case %d: %d\n", ++cas, dlx.ans);
	}
	return 0;
}
