#include <cstdio>
#include <cstring>

const int GMAX = 10;
const int BMAX = 25;
int bag[BMAX][GMAX];

int G, B, S;
int dp[1<<22];
int cook[GMAX];

void init()
{
	memset(bag, 0, sizeof(bag));
	memset(cook, 0, sizeof(cook));
	//memset(dp, -1, sizeof(dp));
	for (int i = 0; i < (1<<B); i++) dp[i] = -1;
}

int MAX(int a, int b) { return a > b ? a : b; }
int dfs(int state, int sum)
{
	if (dp[state] != -1) return dp[state];
	int ret = 0;
	for (int i = 0; i < B; i++)
	if ((state & (1<<i)) == 0)
	{
		int tmp[GMAX];
		int cnt = 0;
		for (int j = 1; j <= G; j++)
		{
			tmp[j] = cook[j];
			cook[j] += bag[i][j];
			if (cook[j] >= S) cnt+=cook[j]/S, cook[j]%=S;
		}
		if (cnt > 0)
			ret = MAX(ret, dfs(state|(1<<i), sum-cnt) + cnt);
		else ret = MAX(ret, sum - dfs(state|(1<<i), sum));
		for (int j = 1; j <= G; j++)
			cook[j] = tmp[j];
	}
	dp[state] = ret;
	return ret;
}

int main()
{
	while (scanf("%d%d%d", &G, &B, &S) == 3 && G + B + S)
	{
		init();
		for (int i = 0; i < B; i++)
		{
			int n;
			scanf("%d", &n);
			for (int j = 0; j < n; j++)
			{
				int x;
				scanf("%d", &x);
				bag[i][x]++;
			}
		}
		int sum = 0;
		int tol = 0;
		for (int i = 1; i <= G; i++)
		{
			tol = 0;
			for (int j = 0; j < B; j++) tol += bag[j][i];
			sum += tol / S;
		}
		printf("%d\n", 2 * dfs(0, sum) - sum);
	}
	return 0;
}
