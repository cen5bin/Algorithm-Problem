#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int KIND = 26;
const int MAX_SIZE = 135;
struct node
{
     int next[KIND];
     int fail;
     int val;
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
     return c - 'a';
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
     p[now].val = 1; //根据不同的题目而定
}

queue<int> q;
void build_ac()
{
     q.push(0);
     p[0].fail = 0;
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


const int MOD = 100000;
const int MAXN = 35;
typedef unsigned long long ULL;
struct Matrix
{
     ULL a[MAXN][MAXN];
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
               ret.a[i][j] = (ret.a[i][j] + this->a[i][k] * m1.a[k][j]);
              // if (ret.a[i][j] >= MOD) ret.a[i][j] -= MOD;
          }
          return ret;
     }
     Matrix operator ^(ULL x) const
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
	 Matrix sum(ULL n)
	 {
		 Matrix tmp = *this;
		 Matrix aa(sz);
		 aa.one();
		 if (n==1) return tmp;
		 if (n & 1) return (tmp^n) + ((tmp^(n>>1))+aa)*sum(n>>1);
		 return ((tmp^(n>>1))+aa)*sum(n>>1);
	 }
     void print()
     {
          for (int i = 0; i < size; i++)
          {
               for (int j = 0; j < size; j++)
                    printf("%I64u ", a[i][j]);
               puts("");
          }
     }
};

const int N = 100;
char s[N];

ULL exp_mod(ULL a, ULL b)
{
	ULL ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a;
		a = a * a;
		b >>= 1;
	}
	return ret;
}
ULL exp_sum(ULL x, ULL n)
{
	if (n == 1) return x;
	if (n & 1) return exp_mod(x, n) + (1 + exp_mod(x, n>>1))*exp_sum(x,n>>1);
	return (1+exp_mod(x, n>>1))*exp_sum(x, n>>1);
}

int main()
{
	ULL n, l;
	while (scanf("%I64u%I64u", &n, &l) == 2)
	{
		init();
		while (n--)
		{
			scanf("%s", s);
			insert(s, strlen(s));
		}
		build_ac();
		Matrix mm(sz);
		for (int i = 0; i < sz; i++)
		for (int j = 0; j < KIND; j++)
		if (p[i].val == 0 && p[p[i].next[j]].val == 0 && p[p[p[i].next[j]].fail].val == 0)
		mm.a[i][p[i].next[j]]++;
		Matrix tmp = mm.sum(l);
		ULL ans = 0;
		for (int i = 0; i < sz; i++)
			ans += tmp.a[0][i];
		ans = exp_sum(26, l) - ans;
		//if (ans < 0) 
		printf("%I64u\n", ans);
	}
	return 0;
}
