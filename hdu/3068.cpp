#include <cstdio>
#include <cstring>

const int N = 110010;
char s[N];
char tmp[N<<1];
int len;
int p[N<<1];
void pre(char *s, char *tmp)
{
	tmp[0] = '$';
	tmp[1] = '#';
	len = 2;
	for (int i = 0; s[i]; i++)
	{
		tmp[len++] = s[i];
		tmp[len++] = '#';
	}
	tmp[len] = '\0';
}
int MIN(int a, int b) { return a < b ? a : b; }
int MAX(int a, int b) { return a > b ? a : b; }
int calmax(char *s)
{
	pre(s, tmp);
	int mx = 0, pi = 0;
	int ans = 0;
	for (int i = 1; i < len; i++)
	{
		if (mx > i) p[i] = MIN(p[2*pi-i], mx-i);
		else p[i] = 1;
		while (tmp[i-p[i]] == tmp[i+p[i]]) p[i]++;
		if (i+p[i] > mx)
		{
			mx = i + p[i];
			pi = i;
		}
		ans = MAX(ans, p[i]);
	}
	return ans - 1;
}

int main()
{
	while (scanf("%s", s) == 1)
	{
		printf("%d\n", calmax(s));
	}
	return 0;
}
