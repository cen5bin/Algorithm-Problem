#include <cstdio>
#include <cstring>

const int N = 100010;
char s1[N], s2[N];
int flag;
int p[2][N];
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

int count[2][N];
bool match_kmp(char *s1, int n1, char *s2, int n2)
{
     int j = 0;
     for (int i = 1; i <= n1; i++)
     {
          while (j != -1 && s2[j+1] != s1[i]) j = p[flag][j];
          if (j == -1 || s2[j+1] == s1[i]) j++;
		  count[flag][i] = j;
          if (j == n2) j = p[flag][j];
     }
     return 0;
}

void reverse(char *s, int l)
{
	for (int i = 1; i <= l / 2; i++)
	{
		char tmp = s[i];
		s[i] = s[l+1-i];
		s[l+1-i] = tmp;
	}
}
void reverse(int *a, int l)
{
	for (int i = 1; i <= l / 2; i++)
	{
		a[i] = a[i] ^ a[l+1-i];
		a[l+1-i] = a[i] ^ a[l+1-i];
		a[i] = a[i] ^ a[l+1-i];
	}
}

typedef long long LL;
LL a[N], b[N];
int maxx;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s%s", s1+1, s2+1);
		int l1 = strlen(s1+1);
		int l2 = strlen(s2+1);
		flag = 0;
		init_kmp(s2, l2, p[flag]);
		match_kmp(s1, l1, s2, l2);
		reverse(s1, l1);
		reverse(s2, l2);
		flag = 1;
		init_kmp(s2, l2, p[flag]);
		match_kmp(s1, l1, s2, l2);
		LL ans = 0;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		maxx = l2;
		reverse(count[1], l1);

		for (int i = 1; i <= l1; i++)
			a[count[0][i]]++, b[count[1][i]]++;
		for (int i = l2; i > 0; i--)
			a[p[0][i]] += a[i], b[p[1][i]] += b[i];
		for (int i = 1; i < l2; i++)
			ans += a[i] * b[l2-i];
	//	for (int i = 1; i <= l1; i++)
	//	{
	//		while (count[1][i])
	//		{
	//			ans +=  a[l2-count[1][i]];//sum(l2 - count[1][i]);
	//			count[1][i] = p[1][count[1][i]];
	//		}
	//		while (count[0][i])
	//		{
	//			a[count[0][i]]++;
	//			//plus(count[0][i], 1);
	//			count[0][i] = p[0][count[0][i]];
	//		}
	//	}
		printf("%lld\n", ans);
	}
	return 0;
}
