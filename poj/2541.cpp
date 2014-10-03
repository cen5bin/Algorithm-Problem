#include <cstdio>
#include <cstring>

int d[15][1<<15];
const int N = 1010010;
char s[N];
int MIN(int a, int b)
{
	return a < b ? a : b;
}

int ans[1010];
int main()
{
	int n, l;
	while (scanf("%d%d", &n, &l) == 2)
	{
		scanf("%s", s);
		memset(d, -1, sizeof(d));
		for (int i = MIN(13, n-1); i >= 1; i--)
		{
			int k = 0;
			for (int j = 0; j < i; j++) k = k << 1 | (s[j] - '0');
			d[i][k] = 0;
			for (int j = i; j < n - 1; j++)
			{
				k = (k & ((1<<(i-1))-1)) << 1 | (s[j] - '0');
				d[i][k] = j - i + 1;
			}
		}
		int ll = n;
		for (int i = 0; i < l; i++)
		{
			int k = 0;
			int tmp = MIN(13, n-1);
			for (int j = n - tmp; j < n; j++) k = k << 1 | (s[j] - '0');
			bool yes = 0;
			if (d[tmp][k] != -1) 
			{ 
				s[n] = s[d[tmp][k] + tmp];
				n++;
				yes = 1;
			}
			for (int j = tmp - 1; !yes && j > 0; j--)
			{
				k = k & ((1<<j)-1);
				if (d[j][k] != -1)
				{
					s[n] = s[d[j][k]+j];
					n++;
					yes = 1;
					break;
				}
			}
			if (!yes) 
			{
				s[n] = '0';
				n++;
			}
			tmp = MIN(13, n-1);
			k = 0;
			for (int j = n - tmp - 1; j < n - 1; j++) k = k << 1 | (s[j] - '0');
			d[tmp][k] = n - tmp - 1;
			for (int j = tmp - 1; j; j--)
			{
				k = k & ((1<<j)-1);
				d[j][k] = n - j - 1;
			}
		}
		s[n] = '\0';
	//	printf("%d\n", n);
		puts(s+ll);
	}
	return 0;
}
