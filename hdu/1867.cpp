#include <cstdio>
#include <cstring>
const int N = 100010;
char s1[N], s2[N], s[N<<1];
int p[N<<1];
void init_kmp(char *s, int n, int *p)
{
	p[0] = -1;
	p[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i-1];
		while (j !=- 1 && s[j+1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}


char ans[N<<1], tmp[N<<1];
int len;
void work(char *s1, char *s2)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	for (int i = 1; i <= l2; i++) s[i] = s2[i-1];
	for (int i = 1; i <= l1; i++) s[i+l2] = s1[i-1];
	init_kmp(s, l1 + l2, p);
	if (p[l1+l2] < len) return;
	if (p[l1+l2] >= l1 || p[l1+l2] >= l2)
	{
		if (l1 > l2)
		{
			if (len < p[l1+l2] || strcmp(ans, s1) > 0)
			strcpy(ans, s1);
		}
		else 
		{
			if (len < p[l1+l2] || strcmp(ans, s2) > 0)
			strcpy(ans, s2);
		}
	}
	else
	{
		strcpy(tmp, s1);
		strcpy(tmp+l1, s2+p[l1+l2]);
		if (len < p[l1+l2] || strcmp(ans, tmp) > 0)
			strcpy(ans, tmp);
	}
	if (len < p[l1+l2]) len = p[l1+l2];
}

int main()
{
	while (scanf("%s%s", s1, s2) == 2)
	{
		len = -1;
	//	memset(ans, 0, sizeof(ans));
		work(s1, s2);
		work(s2, s1);
		puts(ans);
	}
	return 0;
}
