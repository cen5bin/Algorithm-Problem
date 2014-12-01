#include <cstdio>
#include <cmath>

int a[110];

int main()
{
	int m, s;
	while (scanf("%d%d", &m, &s) == 2)
	{
		if (m == 1 && s == 0)
		{
			printf("0 0\n");
			continue;
		}
		if (s == 0 || s > 9 * m)
		{
			puts("-1 -1");
			continue;
		}
		int x = m, y = s;
		if ((x-1) * 9 >= s) 
		{
			a[0] = 1;
			y--;
			x--;
			int cnt = 1;
			while ((x-1)*9>=y) a[cnt++] = 0, x--;
			a[cnt++] = y - (x-1) * 9;
			for (int i = cnt; i < m; i++) a[i] = 9;
			for (int i = 0; i < m; i++) printf("%d", a[i]);
			printf(" ");
			y = s;
			cnt = 0;
			while (y >= 9) 
			{
				cnt++;
				printf("9");
				y-= 9;
			}
			printf("%d", y);
			cnt++;
			for (int i = cnt; i < m; i++) printf("0");
			puts("");
		}
		else
		{
			printf("%d", s - (x-1) * 9);
			for (int i = 0; i < m-1; i++) printf("9");
			printf(" ");
			for (int i = 0; i < m-1; i++) printf("9");
			printf("%d\n", s - (x-1) * 9);
		}
	}
	return 0;
}

