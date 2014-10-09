#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N = 500010;
char s1[N], s2[N];
int next[N], ex[N];

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

int x[30];
bool a1[N], a2[N];
int sum[N];
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		for (int i = 0; i < 26; i++) scanf("%d", &x[i]);
		scanf("%s", s1+1);
		int l = strlen(s1+1);
		for (int i = 1; i <= l; i++)
			s2[i] = s1[l+1-i];
		s2[l+1] = '\0';
		getNext(s2, l);
		getEx(s1, l, s2, l);
		for (int i = 1; i <= l; i++)
		{
			if (i + ex[i] - 1 == l) a1[i] = 1;
			else a1[i] = 0;
		}
		getNext(s1, l);
		getEx(s2, l, s1, l);
		for (int i = 1; i <= l; i++)
		{
			if (i + ex[i] -1 == l) a2[l+1-i] = 1;
			else a2[l+1-i] = 0;
		}
		sum[0] = 0;
		for (int i = 1; i <= l; i++)
			sum[i] = sum[i-1] + x[s1[i] - 'a'];
		int ans = 0;
		for (int i = 1; i < l; i++)
		{
			int tmp = 0;
			if (a2[i]) tmp += sum[i];
			if (a1[i+1]) tmp += sum[l] - sum[i];
			ans = MAX(ans, tmp);
		}
		printf("%d\n", ans);
	} 
	return 0;
}
