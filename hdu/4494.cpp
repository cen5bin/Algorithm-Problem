#include <cstdio>
#include <cstring>

const int N = 500010;
typedef unsigned int UI;
UI f[N], F[N], ans[N];
UI  phi[N];
bool check[N];
void getPhi()
{
	for (int i = 1; i < N; i++) phi[i] = i;
	memset(check, 0, sizeof(check));
	for (int i = 2; i < N; i++)
	if (!check[i])
	{
		phi[i] = i - 1;
		for (int j = i * 2; j < N; j+=i)
		{
			phi[j] = phi[j] / i * (i-1);
			check[j] = 1;
		}
	}
}
typedef long long LL;
void pre()
{
	f[1] = 1;
	for (int i = 2; i < N; i++) f[i] = ((LL)phi[i]*(LL)i)/2;
	memset(F, 0, sizeof(F));
	for (int i = 1; i < N; i++)
	for (int j = i; j < N; j+=i)
		F[j] += f[i];
	memset(ans, 0, sizeof(ans));
	for (UI i = 1; i < N; i++)
	for (UI j = i; j < N; j+=i)
		ans[j] += j * i * F[j/i];
	//for (int i = 1; i < 4; i++) printf("%d ", ans[i]);
	for (int i = 1; i < N; i++)
		ans[i]+=ans[i-1];
//	for (int i = 1; i <)
}
int main()
{
	getPhi();
	//for (int i = 1; i <= 20; i++) printf("%u ", phi[i]);
	pre();
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T--)
	{
		int n;
		scanf("%d", &n);
		printf("Case #%d: %u\n", ++cas, ans[n]);
	}
	return 0;
}
