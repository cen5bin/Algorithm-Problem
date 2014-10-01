#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 10010;
int a[N], dp[N][2], s[N][2];
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		int n, m;
		scanf("%d%d", &n ,&m);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if (m >= n)
		{
			printf("Case %d: %d\n", ++cas, 0);
			continue;
		}
		sort(a, a+n+1);
		int now = 0;
		for (int i = 1; i <= n; i++) dp[i][now] = (a[i]-a[1])*(a[i]-a[1]), s[i][now] = 1;
		//now = 1;
		for (int j = 2; j <= m; j++)
		{
			now = 1 - now;
			for (int i = j; i <= n; i++)
			{
				dp[i][now] = 0x7fffffff;
				for (int k = s[i-1][1-now]; k < i; k++)
				if (dp[i][now] >= dp[k][1-now] + (a[i]-a[k+1])*(a[i]-a[k+1]))
				{
					dp[i][now] = dp[k][1-now] + (a[i]-a[k+1])*(a[i]-a[k+1]);
					s[i][now] = k;
				}
			}
		}
		printf("Case %d: %d\n", ++cas, dp[n][now]);
	}
	return 0;
}
