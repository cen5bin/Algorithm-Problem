#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N = 100010;
char s1[N<<1], s2[N];
int next[N], ex[N];
int p[N];
void init_kmp(char *s, int n)
{
	p[0] = -1;
	p[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		int j = p[i-1];
		while (j != -1 && s[j+1] != s[i]) j = p[j];
		p[i] = j + 1;
	}
}

void getNext(char *s, int n)
{
	next[1] = n;
	int j = 1;
	while (j + 1 <= n && s[j+1] == s[j]) j++;
	next[2] = j - 1;
	int a = 2;	
	for (int i = 3; i <= n; i++)
	{
		int p = next[a] + a - 1;
		int l = next[i-a+1];
		if (i+l-1 < p) next[i] = l;
		else
		{
			int j = MAX(p + 1, i);
			while (j <= n && s[j] == s[j-i+1]) j++;
			next[i] = j - i;
			a = i;
		}
	}
}

void getEx(char *s1, int n1, char *s2, int n2)
{
	int j = 1;
	while (j <= n1 && j <= n2 && s1[j] == s2[j]) j++;
	ex[1] = j - 1;
	int a = 1;
	for (int i = 2; i <= n1; i++)
	{
		int p = ex[a] + a - 1;
		int l = next[i-a+1];
		if (i+l-1 < p) ex[i] = l;
		else 
		{
			int j = MAX(i, p+1);
			while (j <= n1 && j-i+1 <= n2 && s1[j] == s2[j-i+1]) j++;
			ex[i] = j - i;
			a = i; 
		}
	}
}

int ans[3];
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	while (t--)
	{
		scanf("%s", s2+1);
		int l = strlen(s2+1);
		strcpy(s1+1, s2+1);
		strcpy(s1+1+l, s2+1);
		s1[2*l] = '\0';
		init_kmp(s2, l);
		int kk = l;
		if (l % (l - p[l]) == 0) kk = l - p[l];
		getNext(s2, l);
		getEx(s1, 2*l-1, s2, l);
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= kk; i++)
		{
			if (ex[i] == l) ans[1]++;
			else if (s1[i+ex[i]] > s2[ex[i]+1]) ans[2]++;
			else ans[0]++;
		}
		printf("Case %d:", ++cas);
		for (int i = 0; i < 3; i++) printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}
