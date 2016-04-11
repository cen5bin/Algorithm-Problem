#include <cstdio>

int main()
{
	int n, s;
	while (scanf("%d%d", &n, &s) == 2)
	{
		s *= 100;
		int ans = -1;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			int tmp = s - x * 100 - y;
			if (tmp < 0) continue;
			tmp %= 100;
			if (tmp  > ans) ans = tmp;
		}
		printf("%d\n", ans);
	}
	return 0;
}
