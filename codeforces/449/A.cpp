#include <cstdio>
#include <cstring>

long long max(long long a,long long b)
{
	return a>b?a:b;
}

int main()
{
	long long n,m,k;
	while (scanf("%lld%lld%lld", &n, &m, &k)==3) 
	{
		n--;
		m--;
		if (n-k<-m)
		{
			puts("-1");
			continue;
		}
		long long ans = 0;
		if (n>=k)
			ans = max(ans, (n+1)/(k+1)*(m+1));
		else 
			ans = max(ans,(m+1)/(k-n+1));
		if (m>=k) ans = max(ans, (m+1)/(k+1)*(n+1));
		else ans = max(ans, (n+1)/(k-m+1));
		printf("%lld\n", ans);
	}
	return 0;
}
