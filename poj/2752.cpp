#include <cstdio>
#include <cstring>

const int N = 400010;
int p[N];
char s[N];
void init_kmp(char *s, int n, int *p)
{
	p[1] = 0;
	p[0] = -1;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i - 1];
		while (j != -1 && s[j + 1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}

int ans[N];
int main()
{
	while (scanf("%s", s + 1) == 1)
	{
		int n = strlen(s + 1);
		init_kmp(s, n, p);
		int cnt = 0;
		while (n)
			ans[cnt++] = n, n = p[n];
		for (int i = cnt - 1; i >= 0; i--)
		if (ans[i])
		{
			if (i < cnt - 1) printf(" ");
			printf("%d", ans[i]);
		}
		puts("");
	}
}
