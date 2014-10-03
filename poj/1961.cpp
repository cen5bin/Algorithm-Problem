#include <cstdio>
#include <cstring>

const int N = 1000010;
char s[N];
int p[N];

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

int dp[N];

int main()
{
	int n;
	int cas = 0;
	while (scanf("%d", &n) && n)
	{
		scanf("%s", s+1);
		init_kmp(s, n, p);
		for (int i = 1; i <= n; i++)
		if (p[i] == 0) dp[i] = 1;
		else 
		{
			int k = i - p[i];
			if (p[i] / dp[p[i]] != k) dp[i] = 1;
			else dp[i] = dp[p[i]] + 1;
		}
		printf("Test case #%d\n", ++cas);
		for (int i = 1; i <= n; i++)
		if (dp[i] > 1)
			printf("%d %d\n", i, dp[i]);
		puts("");
	}
	return 0;
}
