#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define esp 1e-9
#define inf 0x7fffffff
#define MOD 1000000007
typedef long long LL;

const int N = 1000010;
char s[N], s1[N<<1];
int p[N<<1];
int manacher()
{
    s1[0] = '$';
    s1[1] = '#';
    int len = 2;
    for (int i = 0; s[i]; ++i) s1[len++] = s[i], s1[len++] = '#';
    s1[len++] = '\0';
    int id = 0;
    p[0] = 1;
    int ret = 1, ans = 0;
    for (int i = 1; i < len; ++i)
    {
        if (id + p[id] - 1 > i)
            p[i] = min(p[2*id-i], id + p[id] - i);
        else p[i] = 1;
        while (s1[i+p[i]] == s1[i-p[i]]) p[i]++;
        if (i + p[i] > id + p[id]) id = i;
        if (p[i] - 1 > ret) ret = p[i] - 1, ans = i;

    }
    int x = 0;
    for (int i = ans - p[ans] + 1; i < ans + p[ans] - 1; ++i)
        if (s1[i] != '#')
            s1[x++] = s1[i];
    s1[x++] = '\0';
    return ret;
}

int main()
{
    while (scanf("%s", s) == 1) 
    {
        if (s[0] == 'E') break;
        int ret = manacher();
        static int cas = 1;
        printf("Case %d: %d\n", cas++, ret);
    }
    return 0;
}

