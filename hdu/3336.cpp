#include <cstdio>
#include <cstring>

const int N = 200010;
int p[N];
char s[N];
void init_kmp(char *s, int n)
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
const int MOD = 10007;
int dp[N];
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		scanf("%s", s+1);
		init_kmp(s, n);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) dp[p[i]]++;
		for (int i = n; i >= 1; i--)
		{
			dp[p[i]] = (dp[p[i]] + dp[i]) % MOD;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = (ans + dp[i]) % MOD;
		ans = (ans + n) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
