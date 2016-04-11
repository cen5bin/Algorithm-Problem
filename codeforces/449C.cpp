#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

long long p[100010];
int main()
{
	p[0] = 2;
	int cnt = 1;
	for (long long i = 3; i<100010; i+=2)
	{
		bool heshu = 0;
		for (int j = 0; j < cnt && p[j] * p[j] <= i; j++)
			if (i % p[j] == 0) 
			{
				heshu = 1;
				break;
			}
		if (!heshu)
			p[cnt++] = i;
	}

	long long n;
	while (cin>>n) 
	{
		bool vis[100010]={0};
		int even = n / 2;
		int ans = 0;
		for (int i = 1; p[i] * 2 <=n; i++)
		{
			int tmp = 0;
			for (int j = p[i]; j <= n; j+=p[i])
			if (!vis[j])
			{
				tmp++;
				vis[j] = 1;
				if (j % 2 == 0) even--;
			}
			ans+=tmp/2;
			if (tmp % 2 == 1) even++;
		}
		ans+=even/2;
		cout<<ans<<"\n";
		memset(vis, 0, sizeof(vis));

		int a[100010];
		int k = 0;
		for (int i = 1; p[i] * 2 <=n; i++)
		{
			vector<int>aa;
			k = 0;
			for (int j = p[i]; j <= n; j+=p[i])
			if (!vis[j])
			{
				vis[j] = 1;
				aa.push_back(j);
				k++;
			}

			int size = aa.size(); 
			if (k % 2 == 1) 
			{
				vector<int>::iterator iter;
				for (iter = aa.begin(); iter != aa.end(); iter++)
					if (*iter % 2 == 0)
					{
						vis[*iter] = 0;
						aa.erase(iter);
						break;
					}
				for (int i = 0; i < size - 1; i+=2)
					cout<<aa[i]<<" "<<aa[i+1]<<"\n";
			}
			else 
			{

				for (int i = 0; i < size; i+=2)
					cout<<aa[i]<<" "<<aa[i+1]<<"\n";
			}
		}
		k = 0;
		for (int i = 2; i <= n; i+=2)
		if (!vis[i])
		{
			a[k++] = i;
		}
		for (int i = 0; i < k/2*2; i+=2)
			cout<<a[i]<<" "<<a[i+1]<<"\n";
	}
	return 0;
}
