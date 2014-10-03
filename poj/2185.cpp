#include <cstdio>
#include <cstring>

const int N = 10010;
const int M = 80;
char s[N][M], s1[M][N];
int p[N];
void init_kmp(char *s, int n, int *p)
{
     p[0] = -1;
     p[1] = 0;
     for (int i = 2; i <= n; i++)
     {
          int j = p[i - 1];
          while (j != -1 && s[j+1] != s[i]) j = p[j];
          p[i] = j + 1;
     }
}
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; i++) scanf("%s", s[i]+1);
		int l = 1;
		for (int i = 1; i <= n; i++)
		{
			init_kmp(s[i], m, p);
			l = l * (m - p[m]) / gcd(l, m - p[m]);
			if (l > m)
			{
				l = m;
				break;
			}
		}
		for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			s1[i][j] = s[j][i];
		int r = 1;
		for (int i = 1; i <= m; i++)
		{
			init_kmp(s1[i], n, p);
			r = r * (n - p[n]) / gcd(r, n - p[n]);
			if (r > n)
			{
				r = n;
				break;
			}
		}
		printf("%d\n", r * l);
	}
	return 0;
}

