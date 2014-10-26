#include <cstdio>
#include <cstring>

const int N = 100010;
int a[N];
int prime[N];
int cnt;
int mu[N];
bool check[N];
void getMu()
{
	memset(check, 0, sizeof(check));
	cnt = 0;
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
			if (i % prime[j] == 0) mu[i*prime[j]] = 0;
			else mu[i * prime[j]] = -mu[i];
		}
	}

}


int count[N];
int mul[N];
int col[N];
typedef long long LL;
int main()
{
	getMu();
	int T;
	scanf("%d", &T);
	while (T--)
	{
		LL n;
		scanf("%lld", &n);
		memset(count, 0, sizeof(count));
		for (int i = 0; i < n; i++) 
		{
			scanf("%d", &a[i]);
			count[a[i]]++;
		}
		memset(mul, 0, sizeof(mul));
		for (int i = 1; i < N; i++)
		for (int j = i; j < N; j+=i)
			mul[i] += count[j];
		memset(col, 0, sizeof(col));
		for (int i = 1; i < N; i++)
		for (int j = i; j < N; j+=i)
			col[j] += mul[i] * mu[i];
//		for (int i = 0; i < n; i++)
//			printf("%d %d\n", i, col[a[i]]);
		LL ans = n * (n-1) * (n-2) / 6;
		LL cc = 0;
		col[1]--;
		for (int i = 0; i < n; i++)
		{
		//	if (a[i] != 1)
			cc += (LL)col[a[i]] * (n-1-col[a[i]]);

		}
		printf("%lld\n", ans - cc / 2);

	}
	return 0;
}
