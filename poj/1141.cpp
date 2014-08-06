#include <cstdio>
#include <cstring>

char s[110];
int dp[110][110];
int path[110][110];

void printans(int a, int b)
{
	if (a > b) return;
	if (a==b)
	{
		if (s[a]=='('||s[a]==')') printf("()");
		else if (s[a]=='['||s[a]==']') printf("[]");
		return;
	}
	if (path[a][b] == -1)
	{
		printf("%c", s[a]);
		printans(a+1, b-1);
		printf("%c", s[b]);
	}
	else 
	{
		printans(a, path[a][b]);
		printans(path[a][b]+1, b);
	}
}

int main()
{
	while(gets(s))
	{
		int l = strlen(s);
		for (int i = 0; i < l; i++)
		dp[i][i] = 1;
		for (int i = 2; i <= l; i++)
		for (int j = 0; j < l; j++)
		{
			if (j+i-1>=l) break;
			int a = j;
			int b = j+i-1;
			dp[a][b] = 10000;
			if ((s[a] == '[' && s[b] == ']') || (s[a]=='(' && s[b] == ')'))
			{
				dp[a][b] = (b==a+1)?0:dp[a+1][b-1];
				path[a][b] = -1;
			}
			for (int k = a; k < b; k++)
			{
				if (dp[a][b] > dp[a][k] + dp[k+1][b])
				{
					dp[a][b] = dp[a][k] + dp[k+1][b];
					path[a][b] = k;
				}
			}
		}
		printans(0, l-1);
		puts("");
	}
	return 0;
}
