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

const int N = 110;
const int M = 100010;
int a[N*10];
int b[N], c[N];
bool dp[M];

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n + m)
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            x = b[i], y = c[i];
            int tmp = 1;
            while (y >= tmp)
            {
                y -= tmp;
                a[cnt++] = x * tmp;
                tmp <<= 1;
            }
            if (y) a[cnt++] = y * x;
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int j = 0; j < cnt; ++j)
        for (int i = m; i >= a[j]; --i)
            dp[i] |= dp[i-a[j]];
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            if (dp[i]) ans++;
        printf("%d\n", ans);
    }
    return 0;
}

