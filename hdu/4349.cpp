#include <cstdio>
#include <cstring>
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int cnt = 0;
		while (n)
		{
			if (n & 1) cnt++;
			n>>=1;
		}
		printf("%d\n", 1<<cnt);
	}
	return 0;
}