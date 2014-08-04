#include <cstdio>
#include <cstring>
#include <cmath>
#define esp 1e-8
double logn[500010];
int main()
{
	int n;
	double p;
	int cas = 1;
	for (int i = 1; i < 500010; i++)
		logn[i] = log(i);
	while (scanf("%d%lf", &n, &p) == 2)
	{
		if (fabs(p)<esp || fabs(1-p)<esp)
		{
			printf("Case %d: %d\n", cas++, n);
			continue;
		}
		double logp = log(p);
		double logq = log(1-p);
		double q = 1 - p;
		double tmp = 0;
		double aa = 0;
		for (int i = 1; i <= n; i++)
			aa += logn[i];
		tmp = aa;
		double ans = 0;
		for (int i = 0; i <= n; i++)
		{
			double x = 0;
			x+=exp(tmp-aa+(n+1)*logp+i*logq);
			x+=exp(tmp-aa+(n+1)*logq+i*logp);
			ans +=x*(n-i);
			tmp += logn[n+i+1] - logn[i+1];
		}
		printf("Case %d: %.6lf\n", cas++, ans);
	}
	return 0;
}
