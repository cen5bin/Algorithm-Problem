#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define MIN(a, b) (((a) < (b))? (a):(b))
#define MAX(a, b) (((a) > (b))? (a):(b))
const int N = 50010;
const int M = 16; // (1<<M)要大于N
int a[N];
int dp_min[N][M], dp_max[N][M];
int dd[30];
void rmq_init(int n)
{
	for (int i = 0; i <= M; i++)
		dd[i] = 1 << i;
	for (int i = 1; i <= n; i++)
		dp_min[i][0] = dp_max[i][0] = a[i];
	for (int j = 1; j < M; j++)
	for (int i = 1; i <= n; i++)
	if (i+(1<<j)-1 <= n)
		dp_min[i][j] = MIN(dp_min[i][j-1], dp_min[i+dd[j-1]][j-1]),
		dp_max[i][j] = MAX(dp_max[i][j-1], dp_max[i+dd[j-1]][j-1]);
}

int rmq_query(int l, int r)
{
	int k = lower_bound(dd, dd+M+1, r-l+1)-dd;
	if (k) k--;
	return MAX(dp_max[l][k], dp_max[r-dd[k]+1][k]) - MIN(dp_min[l][k], dp_min[r-dd[k]+1][k]);
}

int main()
{
	int n, q;
	while (scanf("%d%d", &n, &q) == 2)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		rmq_init(n);
		while (q--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%d\n", rmq_query(x, y));
		}
	}
	return 0;
}
