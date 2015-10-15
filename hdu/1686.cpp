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
const int M = 10010;
char s[N];
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
int match(int *a, int n1, int *b, int n2)
{
    int ret = 0;
    int j = 0;
    for (int i = 1; i <= n2; ++i)
    {
        while (~j && a[j+1] != b[i]) j = p[j];
        j++;
        if (j == n1)
        {
            ret++;
            j = p[j];
        }
    }
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = 0;
        for (int i = 0; s[i]; ++i) a[++n] = s[i] - 'A';
        scanf("%s", s);
        int m = 0;
        for (int i = 0; s[i]; ++i) b[++m] = s[i] - 'A';
        init(a, n);
        printf("%d\n", match(a, n, b, m));
    }
    return 0;
}

