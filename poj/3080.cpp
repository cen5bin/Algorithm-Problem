#include <cstdio>
#include <cstring>

const int N = 65;
const int M = 12;
char s[M][N];
int p[N];
void init_kmp(char *s, int n, int *p)
{
	p[1] = 0;
	p[0] = -1;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i-1];
		while (j !=- 1 && s[j+1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}

bool match_kmp(char *s1, int n1, char *s2, int n2)
{
	int j = 0;
	for (int i = 1; i <= n1; i++)
	{
		while (j != -1 && s1[i] != s2[j+1]) j = p[j];
		if (j == -1 || s1[i] == s2[j+1]) j++;
		if (j == n2) return 1;
	}
	return 0;
}

char ans[N];
int ans_len;

int main()
{
//	init_kmp("aaaa", 3, p);
//	if (match_kmp("aaaa", 3, "aaaa", 3)) puts("yes"); else puts("no");
//	for (int i = 1; i <= 8; i++) printf("%d ", p[i]);
	//init_kmp("aCATCATCAT", 9, p);
	//if (match_kmp("aAACATCATCATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT", 60, "aCATCATCAT", 9)) puts("yes");
//	else puts("no");
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) scanf("%s", s[i]+1);
		int low = 2, high = 60;
		ans[0] = '\0';
		ans_len = 0;
		while (low < high)
		{
			int mid = (low + high + 1) >> 1;
			bool find = 0;
			for (int i = 1; i + mid - 1 <= 60; i++)
			{
				init_kmp(s[1]+i-1, mid, p);
				bool yes = 1;
				for (int j = 2; yes && j <= m; j++)
					yes &= match_kmp(s[j], 60, s[1]+i-1, mid);
				if (yes) 
				{
					if (mid > ans_len || (mid == ans_len && strncmp(ans, s[1]+i-1, mid) > 0)) {
					strncpy(ans, s[1]+i, mid);
					ans[mid] = '\0';
					ans_len = mid;
					}
				}
				
				find |= yes;
			}
			if (find) low = mid;
			else high = mid - 1;
		}
		//printf("%d\n", ans_len);
		if (ans_len < 3) puts("no significant commonalities");
		else puts(ans);
	}
	return 0;
}
