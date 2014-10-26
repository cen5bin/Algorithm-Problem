#include <cstdio>
#include <cstring>

const int N = 500010;
int prime[N];
int cnt;
int mu[N];
bool check[N];
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
			if (i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) mu[i * prime[j]] = 0;
			else mu[i * prime[j]] = -mu[i];
		}
	}
}

typedef long long LL;
int x[N];
int y[N];
int num[N];
int f[N][25];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main()
{
	getMu();
	memset(num, 0, sizeof(num));
	for (int i = 0; i < cnt; i++)
		for (LL j = prime[i]; j < N; j = j * prime[i])
		for (int k = j; k < N; k+=j)
			num[k]++;
	memset(f, 0, sizeof(f));
	for (int i = 1; i < N; i++)
		for (int j = i; j < N; j+=i)
		f[j][num[i]] += mu[j/i];
	for (int i = 1; i < N; i++)
		for (int j = 1; j < 25; j++)
			f[i][j] += f[i][j-1];
	for (int i = 1; i < N; i++)
		for (int j = 0; j < 25; j++)
			f[i][j] += f[i-1][j];

	int T;
	scanf("%d", &T);
	while (T--)
	{
		LL n, m, p;
		scanf("%lld%lld%lld", &n, &m, &p);
		LL ans = 0;
		if (n > m)
		{
			n = n ^ m;
			m = n ^ m;
			n = n ^ m;
		}
		for (int i = 1; i <= n; i++)
		{
			int k = MIN(n/(n/i), m/(m/i));
			ans += (f[k][p] - f[i-1][p])*(n/i)*(m/i);
			i = k;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
