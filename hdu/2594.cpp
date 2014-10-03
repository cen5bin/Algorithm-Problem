#include <cstdio>
#include <cstring>
const int N = 50010;
char s1[N], s2[N], s[N<<1];

int p[N<<1];
void init_kmp(char *s, int n, int *p)
{
	p[0] = -1;
	p[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i-1];
		while (j != -1 && s[j+1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}

int main()
{
	while (scanf("%s%s", s1, s2) == 2)
	{
		int l1 = strlen(s1);
		int l2 = strlen(s2);
		for (int i = 1; i <= l1; i++) s[i] = s1[i-1];
		for (int i = 1; i <= l2; i++) s[i+l1] = s2[i-1];
		init_kmp(s, l1+l2, p);
		if (p[l1+l2] >= l1 || p[l1+l2] >= l2)
		{
			if (l1 < l2)
				printf("%s %d\n", s1, l1);
			else printf("%s %d\n", s2, l2);
		}
		else 
		{
			if (p[l1+l2] == 0) puts("0");
			else 
			{
				s1[p[l1+l2]] = '\0';
				printf("%s %d\n", s1, p[l1+l2]);
			}
		}
	}
	return 0;
}
