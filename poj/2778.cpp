#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_SIZE = 110;
const int KIND = 4;
struct node
{
	int next[KIND];
	int val, fail;
	void init()
	{
		val = fail = 0;
		memset(next, 0, sizeof(next));
	}
}p[MAX_SIZE];
int sz;
void init()
{
	sz = 1;
	p[0].init();
}
inline int idx(char c)
{
	if (c == 'A') return 0;
	if (c == 'T') return 1;
	if (c == 'G') return 2;
	if (c == 'C') return 3;
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
		int now = q.front();
		q.pop();
		for (int i = 0; i < KIND; i++)
		if (p[now].next[i] != 0)
		{
			if (now == 0) p[p[now].next[i]].fail = 0;
			else p[p[now].next[i]].fail = p[p[now].fail].next[i];
			q.push(p[now].next[i]);
		}
		else 
		{
			if (now == 0) p[now].next[i] = 0;
			else p[now].next[i] = p[p[now].fail].next[i];
		}
	}
}

const int MOD = 100000;
const int N = 20;
char s[N];

const int MAXN = 110;
typedef long long LL;
struct Matrix
{
	LL a[MAXN][MAXN];
	int size;
	Matrix(){memset(a, 0, sizeof(a));}
	Matrix(int _size):size(_size){ memset(a, 0, sizeof(a)); }
	void one()
	{
		memset(a, 0, sizeof(a));
		for (int i = 0; i < size; i++)
			a[i][i] = 1;
	}
	Matrix operator +(const Matrix &m1) const
	{
		Matrix ret(size);
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			ret.a[i][j] = this->a[i][j] + m1.a[i][j];
		return ret;
	}
	Matrix operator *(const Matrix &m1) const 
	{
		Matrix ret(size);
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		for (int k = 0; k < size; k++)
		{
			ret.a[i][j] = (ret.a[i][j] + this->a[i][k] * m1.a[k][j] % MOD);
			if (ret.a[i][j] >= MOD) ret.a[i][j] -= MOD;
		}
		return ret;
	}
	Matrix operator ^(int x) const
	{
		Matrix ret(size);
		Matrix tmp = *this;
		ret.one();
		while (x)
		{
			if (x & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			x >>= 1;
		}
		return ret;
	}
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				printf("%d ", a[i][j]);
			puts("");
		}
	}
};

int main()
{
	int n, m;
	while (scanf("%d%d", &m, &n) == 2)
	{
		init();
		while (m--)
		{
			scanf("%s", s);
			insert(s, strlen(s));
		}
		build_ac();
		Matrix mm(sz);
		for (int i = 0; i < sz; i++)
		for (int j = 0; j < KIND; j++)
			if (p[p[i].next[j]].val == 0 && p[i].val == 0 && p[p[p[i].next[j]].fail].val == 0)
				mm.a[i][p[i].next[j]]++;
//		mm.print();
		Matrix tmp = mm ^ n;
//		tmp.print();
		int ans = 0;
		for (int i = 0; i < sz; i++)
			ans = (ans + tmp.a[0][i]) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}

