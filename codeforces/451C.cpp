#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		long long n,k,d1,d2;
		cin>>n>>k>>d1>>d2;
		if (n % 3)
		{
			puts("no");
			continue;
		}
		bool yes = 0;
		for (int i = 0; !yes&&i < 2; i++)
		for (int j = 0; !yes&&j < 2; j++)
		{
			int a1 = i * 2 - 1;
			int a2 = j * 2 - 1;
			long long x1, x2, x3;
			long long D1 = a1 * d1;
			long long D2 = a2 * d2;
			if (k - D1 - D2 < 0 || (k - D1 - D2) % 3) 
				continue;
			x2 = (k-D1-D2)/3;
			x1 = x2 + D1;
			x3 = x2 + D2;
			if (x1<0||x3<0) continue;
			if (x1 + x2 + x3 > k)
				continue;	
			long long x = max(x1, max(x2, x3));
			if (x*3-x1-x2-x3<=n-k)
				yes = 1;
		}
		if (yes)
			puts("yes");
		else puts("no");
	}
	return 0;
}
