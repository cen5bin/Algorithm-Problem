//AC automation+dp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_SIZE = 1010;
const int KIND = 26;
struct node
{
	int next[KIND];
	int fail;
	int val;
	void init()
	{
		fail = val = 0;
		memset(next, 0, sizeof(next));
	}
}p[MAX_SIZE];
int sz;
inline int idx(char c)
{
	return c - 'a';
}
void init()
{
	sz = 1;
	p[0].init();
}
void insert(char *s, int n)
{
	int now = 0;
	for (int i = 0; i < n; i++)
	{
		int index = idx(s[i]);
		if (p[now].next[index] == 0)
		{
			p[now].next[index] = sz;
			p[sz++].init();
		}
		now = p[now].next[index];
	}
	p[now].val = 1;
}
queue<int> q;
void build_ac()
{
	q.push(0);
	while (!q.empty())
	{
		int tmp = q.front();
		q.pop();
		for (int i = 0; i < KIND; i++)
		if (p[tmp].next[i])
		{
			if (tmp == 0) p[p[tmp].next[i]].fail = 0;
			else p[p[tmp].next[i]].fail = p[p[tmp].fail].next[i];
			q.push(p[tmp].next[i]);
		}
		else 
		{
			if (tmp == 0) p[tmp].next[i] = 0;
			else p[tmp].next[i] = p[p[tmp].fail].next[i];
		}
	}
}


int query(char *s, int n)
{
     int ret = 0;
     int now = 0;
     for (int i = 0; i < n; i++)
     {
          int index = idx(s[i]);
          now = p[now].next[index];
          int tmp = now;
          while (tmp != 0 && p[tmp].val != -1)
          {
               ret += p[tmp].val;
               p[tmp].val = -1;
               tmp = p[tmp].fail;
          }
     }
     return ret;
}

double dp[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE];


double pp[KIND];

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) && n + m)
	{
		memset(pp, 0, sizeof(pp));
		for (int i = 0; i < n; i++)
		{
			char c;
			double p0;
			scanf(" %c%lf", &c, &p0);
			pp[idx(c)] = p0;
		}
		scanf("%s", s);
		init();
		insert(s, strlen(s));
		build_ac();
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= m; i++)
		for (int j = 0; j < sz-1; j++)
		{
			for (int k = 0; k < KIND; k++)
				dp[i][p[j].next[k]]+= dp[i-1][j] * pp[k];
		}
		double ans = 0;
		for (int i = 1; i <= m; i++) ans += dp[i][sz-1];
		printf("%.2f%%\n", ans * 100);
	}
	return 0;
}
