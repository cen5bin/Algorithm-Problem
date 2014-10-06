#include <cstdio>
#include <cstring>

const int N = 100010;
const int K = 25010;
int s1[N], s2[K];
int p[K];
int low[K], high[K], occur[K];
int kk[30];
int cnt;
int ans[N];

bool cmp(int *s1, int *s2, int k)
{
	if (s1[occur[s2[k]]] != s1[k]) return 0;
	if (low[k] !=- 1 && s1[low[k]] >= s1[k]) return 0;
	if (high[k] != -1 && s1[high[k]] <= s1[k]) return 0;
	return 1;
}

void init_kmp(int *s, int n, int *p)
{
	p[0] = -1;
	p[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i-1];
		while (j != -1 && !cmp(s+i-j-1, s, j+1)) j = p[j];
		p[i] = j + 1;
	}
}

void match_kmp(int *s1, int n1, int *s2, int n2)
{
	int j = 0;
	for (int i = 1; i <= n1; i++)
	{
		while (j != -1 && !cmp(s1+i-j-1, s2, j+1)) j = p[j];
		if (cmp(s1+i-j-1, s2, j+1) || j == -1) j++;
		if (j == n2) 
		{
			ans[cnt++] = i - n2 + 1;
			//printf("%d\n", i - n2 + 1);
			j = p[j];
		}
	}
}



int main()
{
	int n, k, s;
	while (scanf("%d%d%d", &n, &k, &s) == 3)
	{
		for (int i = 1; i <= n; i++) scanf("%d", &s1[i]);
		for (int i = 1; i <= k; i++) scanf("%d", &s2[i]);
		memset(occur, -1, sizeof(occur));
		memset(low, -1, sizeof(low));
		memset(high, -1, sizeof(high));
		memset(kk, -1, sizeof(kk));
		for (int i = 1; i <= k; i++)
		{
			if (occur[s2[i]] == -1) occur[s2[i]] = i;
			for (int j = s2[i] - 1; j >= 0; j--)
			if (occur[j] != -1) 
			{
				low[i] = occur[j];
				break;
			}
			for (int j = s2[i] + 1; j <= s; j++)
			if (occur[j] != -1)
			{
				high[i] = occur[j];
				break;
			}
		}

		init_kmp(s2, k, p);
		cnt = 0;
		match_kmp(s1, n, s2, k);
		printf("%d\n", cnt);
		for (int i = 0; i < cnt; i++) printf("%d\n", ans[i]);
	}
}
