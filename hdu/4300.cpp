
//getNext 和 getEx是扩展KMP的函数，字符串必须从1开始！！，s2表示模式串
#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N = 100010;
char s1[N<<1], s2[N];
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

char s[N], ss[N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", s);
		for (int i = 0; s[i]; i++) ss[s[i]-'a'] = 'a' + i;
		scanf("%s", s1+1);
		int l = strlen(s1+1);
		for (int i = 1; i <= l / 2; i++)
		{
			s2[i] = ss[s1[i]-'a'];
		}
		s2[l/2+1] = '\0';
		getNext(s2, l/2);
		getEx(s1+l/2, l - l / 2, s2, l / 2);
		int id = l + 1;
		for (int i = l/2 + 1; i <= l; i++)
		{
			if (ex[i-l/2] + i - 1 == l)
			{
				id = i;
				break;
			}
		}
		s1[id] = '\0';
		printf("%s", s1+1);
		for (int i = 1; i < id; i++)
			printf("%c", ss[s1[i] - 'a']);
		puts("");
	}
	return 0;
}
