#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

long long cal(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

int work(long long k, long long n, int r)
{
	long long tmp1 = cal(k, r) - 1;
	long long tmp2 = n * (k - 1);
	if (tmp2 / k > tmp1) return -1;
	if (tmp2 / k < tmp1) return 1;
	if (tmp2 % k == 0) return 0;
	return -1;
}

long long ans;
long long r;
long long k;

int solve(long long n, int i)
{
	long long head = 2;
	long long tail = (long long)pow(n, 1.0 / i)+1;
	int ret = -1;
	if (head < tail) ret = 0;
	while (head < tail)
	{
		long long mid = head + tail >> 1;
		int ret = work(mid, n, i);
		if (ret == 0)
		{
			if (mid * i < ans)
			{
				ans = mid * i;
				r = i;
				k = mid;
			}
			break;
		}
		else if (ret == -1)
			head = mid + 1;
		else tail = mid - 1;
	}
	return ret;
}

int main()
{
	long long n;
	while (cin >> n)
	{
		ans = n - 1;
		r = 1;
		k = n - 1;
		for (int i = 2; ; i++)
		{
			int ret1 = solve(n, i);
			int ret2 = solve(n-1, i);
			if (ret1 == -1 && ret2 == -1) break;
		}
		cout<<r<<" "<<k<<endl;
	}
	return 0;
}
