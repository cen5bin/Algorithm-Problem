#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
int R[N][N];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= m+2; i++)
		for (int j = 1; j <= n+2; j++)
			R[i][j] = 0x7fffffff;
		int ans = 0;
		for (int i = 0; i <= m; i++) R[i][0] = 0;
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			for (int j = m; j >= 0; j--)
			{
				int tmp = lower_bound(R[j], R[j] + n + 1, x) - R[j];
				if (tmp > ans) ans = tmp;
				R[j][tmp] = x;
				if (j)
				{
					tmp = lower_bound(R[j-1], R[j-1] + n + 1, y) - R[j-1];
					if (tmp > ans) ans = tmp;
					if (R[j][tmp] > y)
						R[j][tmp] = y;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
