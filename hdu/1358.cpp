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
int a[N], p[N];
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
    int n;
    while (scanf("%d", &n) && n)
    {
        scanf("%s", s);
        for (int i = 0; i < n; ++i) a[i+1] = s[i];
        init(a, n);
        static int cas = 1;
        printf("Test case #%d\n", cas++);
        for (int i = 2; i <= n; ++i)
        if (p[i] && i % (i-p[i]) == 0)
        {
            int x = i / (i - p[i]);
            printf("%d %d\n", i, x);
        }
        puts("");
    }
    return 0;
}

