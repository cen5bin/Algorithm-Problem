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
const int N = 100010;
int a[N], b[N], p[N];
void init(int *a, int n)
{
    p[0] = -1;
    p[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (~j && a[j+1] != a[i]) j = p[j];
        p[i] = ++j;
    }
}
char s[N];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = 0;
        for (int i = 0; s[i]; ++i) a[++n] = s[i] - 'a';
        init(a, n);
        int ans = 0;
        if (p[n] == 0) ans = n;
        else {
            ans = n % (n - p[n]);
            if (ans) ans = n - p[n] - ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}

