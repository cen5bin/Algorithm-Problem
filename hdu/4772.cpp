#include <cstdio>
#include <cstring>

const int N = 35;
int a[N][N];
int b[N][N];

void rotate(int a[][N], int n)
{
	int tmp[N][N];
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		tmp[j][n-1-i] = a[i][j];
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		a[i][j] = tmp[i][j];
}

int judge(int a[][N], int b[][N], int n)
{
	int ret = 0;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		if (a[i][j] == b[i][j]) ret++;
	return ret;
}


#define MAX(a, b) (a  > b ? a : b)
int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &b[i][j]);
		//for (int x = 0; x < n; x++)
		//{
		//	for (int y = 0; y < n; y++)
		//		printf("%d ", b[x][y]);
		//	puts("");
		//}
		//puts("----------------");

		int ans = 0;
		for (int i = 0; i < 4; i++)
		{
			//for (int x = 0; x < n; x++)
			//{
			//	for (int y = 0; y < n; y++)
			//		printf("%d ", a[x][y]);
			//	puts("");
			//}
			//puts("-------=------");
			ans = MAX(ans, judge(a, b, n));
			rotate(a, n);
		}
		printf("%d\n", ans);
	}
	return 0;
}
