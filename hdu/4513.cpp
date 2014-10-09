#include <cstdio>
#include <cstring>

const int N = 110010;
char s[N];
int tmp[N<<1];
int len;
int p[N<<1];
int x[N];
void pre(int *s, int n, int *tmp)
{
     tmp[0] = -2;
     tmp[1] = -1;
     len = 2;
     for (int i = 0; i < n; i++)
     {
          tmp[len++] = s[i];
          tmp[len++] = -1;
     }
	 tmp[len] = -100;
}
int MIN(int a, int b) { return a < b ? a : b; }
int MAX(int a, int b) { return a > b ? a : b; }
int calmax(int *s, int n)
{
     pre(s, n, tmp);
     int mx = 0, pi = 0;
     int ans = 0;
     for (int i = 1; i < len; i++)
     {
          if (mx > i) p[i] = MIN(p[2*pi-i], mx-i);
          else p[i] = 1;
          while (tmp[i-p[i]] == tmp[i+p[i]]) p[i]++;
          if (i+p[i] > mx)
          {
               mx = i + p[i];
               pi = i;
          }
          ans = MAX(ans, p[i]);
     }
     return ans - 1;
}

int tt[N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &x[i]);
		calmax(x, n);
	//	for (int i = 0; i < len; i++) printf("%d ", p[i]);
	//	puts("");
	///	for (int i = 0; i < n; i++) p[i]--;
		for (int i = 2; i <= n * 2; i+=2) p[i] = MAX(p[i-1], MAX(p[i], p[i+1])); //p[i/2-1] = p[i]-1;//printf("%d ", p[i]);
		for (int i = 2; i <= 2 * n; i+=2) p[i/2-1] = p[i]-1;
	//	for (int i = 0; i < n; i++) printf("%d ", p[i]);
	//	puts("");
		int start = 0;
		for (int i = 1; i < n; i++)
		{
			if (x[i] < 	x[i-1])
			{
				for (int j = start; j < i; j++) tt[j] = j - start + 1;
				start = i;
			}
		}
		for (int j = start; j < n; j++) tt[j] = j - start + 1;
	//	for (int i = 0; i < n; i++) printf("%d ", tt[i]);
		int ans = 1;
		for (int i = 0; i < n; i++)
		{
			int kk = 0;
			if (tt[i] * 2 > p[i]) kk = p[i];
			else kk = tt[i];
			ans = MAX(ans, kk);
		}
		printf("%d\n", ans);
	}
	return 0;
}
