#include <cstdio>
#include <cstring>

int main()
{
	int a[100010];
	int n;
	while (scanf("%d", &n)==1)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		int start = 1;
		int end = 1;
		bool yes = 1;
		int cnt = 0;
		for (int i = 2; i <= n; i++)
			if (a[i] < a[i-1])
			{
				if (++cnt == 2)
				{
					yes = 0;
					break;
				}
				start = i - 1;
				end = i - 1;
				for (; i <= n; i++)
				{
					if (a[i] > a[i-1])
					{
						break;
					}
					end = i;
				}
				if (i <= n && a[start] > a[end+1])
				{
					yes = 0;
					break;
				}
				if (start > 1 && a[start-1] > a[end])
				{
					yes = 0;
					break;
				}
			}
		if (yes)
		{
			puts("yes");
			printf("%d %d\n", start, end);
		}
		else puts("no");
	}
	return 0;
}
