#include <cstdio>
#include <cstring>
int main()
{
	char s[100010];
	int a[100010][2][2];
	while(gets(s+1))
	{
		memset(a, 0, sizeof(a));
		long long ans1 = 0;
		long long ans2 = 0;
		for (int i = 1; s[i]; i++)
		{
			ans1++;
			ans1 += a[i-1][s[i]-'a'][i&1];
			ans2 += a[i-1][s[i]-'a'][1-(i&1)];
			a[i][s[i]-'a'][i&1] = a[i-1][s[i]-'a'][i&1]+1;
			a[i][s[i]-'a'][1-(i&1)] = a[i-1][s[i]-'a'][1-(i&1)];
			a[i][1-(s[i]-'a')][i&1] = a[i-1][1-(s[i]-'a')][i&1];
			a[i][1-(s[i]-'a')][1-(i&1)] = a[i-1][1-(s[i]-'a')][1-(i&1)];
		}
		printf("%lld %lld\n",ans2, ans1);
	}
	return 0;
}
