#include <cstdio>
#include <cstring>

const int N = 100010;
bool check[N];
int mu[N];
int prime[N];
int cnt;
void getMu()
{
	cnt = 0;
	memset(check, 0, sizeof(check));
	mu[1] = 1;
	for (int i = 2; i < N; i++)
	{
		if (!check[i])
		{
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cnt; j++)
		{
			if (i * prime[j] > N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) mu[i * prime[j]] = 0;
			else mu[i * prime[j]] = -mu[i];
		}
	}
}

typedef long long LL;

int main()
{
	getMu();
	int a, b, c, d, k;
	int cas = 0;
	int T;
	scanf("%d", &T);
	while (T-- && scanf("%d%d%d%d%d", &a, &b, &c, &d, &k))
	{
		if (b < k || d < k || k == 0)
		{
			printf("Case %d: 0\n", ++cas);
			continue;
		}
	
		LL n = b / k, m = d / k;
		LL tmp = n;
		if (n > m) tmp = m;
		LL ans = 0;
		LL ans1 = 0;
		for (int i = 1; i <= tmp; i++)
			ans += mu[i] * (n/i) * (m/i), ans1+=mu[i]*(tmp/i)*(tmp/i);
	//	printf("ans=%lld ans1=%lld\n", ans, ans1);
		printf("Case %d: %lld\n", ++cas, ans - ans1 / 2);
	
	}
	return 0;
}
