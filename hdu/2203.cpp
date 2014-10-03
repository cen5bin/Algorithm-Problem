#include <cstdio>
#include <cstring>

const int N = 100010;
char s1[N], s2[N], s[N<<1];
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

bool match_kmp(char *s1, int n1, char *s2, int n2)
{
	int j = 0;
	for (int i = 1; i <= n1; i++)
	{
		while (j != -1 && s2[j+1] != s1[i]) j = p[j];
		if (j == -1 || s2[j+1] == s1[i]) j++;
		if (j == n2) return 1;
	}
	return 0;
}

int main()
{
	while (scanf("%s%s", s1+1, s2+1) == 2)
	{
		int l1 = strlen(s1+1);
		int l2 = strlen(s2+1);
		for (int i = 1; i <= l1; i++)
			s[i] = s[i+l1] = s1[i];
		init_kmp(s2, l2, p);
		if (match_kmp(s, l1*2, s2, l2)) puts("yes");
		else puts("no");
	}
	return 0;
}
