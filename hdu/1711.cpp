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
const int N = 10010;
const int M = 1000010;
int p[N];
int a[N], b[M];
void init(int *a, int n)
{
    p[0] = -1;
    p[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (~j && a[i] != a[j+1]) j = p[j];
        p[i] = ++j;
    }
}
int match(int *a, int n1, int *b, int n2)
{
    int j = 0;
    for (int i = 1; i <= n2; ++i)
    {   
        while (~j && a[j+1] != b[i]) j = p[j];
        ++j;
        if (j == n1)
        {
            return i - n1 + 1;
        }
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
        for (int i = 1; i <= m; ++i) scanf("%d", &a[i]);
        init(a, m);
        printf("%d\n", match(a, m, b, n));
    }
    return 0;
}

