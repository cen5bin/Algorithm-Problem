#include <cstdio>
#include <cstring>

const int N = 1000010;
char s[N];
int p[N];

void init_kmp(char *s, int n, int *p)
{
	p[1] = 0;
	p[0] = -1;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i - 1];
		while (j != -1 && s[j+1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}

int main()
{
	while (scanf("%s", s+1) == 1)
	{
		int len = strlen(s+1);
		if (len == 1 && s[1] == '.') break;
		init_kmp(s, len, p);
		int ff = len;
		int k = len;
		while (k)
		{
			if (ff != len && k - p[k] != ff) break;
			ff = k - p[k];
			k = p[k];
		}
		if (k) puts("1");
		else printf("%d\n", len / ff);
	}
	return 0;
}
