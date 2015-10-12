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
LL dp[N];
int a[N];
LL mm[N];
int main()
{
    int m, n;
    while (scanf("%d%d", &m, &n) == 2)
    {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 0; i <= n; ++i) mm[i] = 0;
        dp[0] = 0;
        LL maxx;
        for (int j = 1; j <= m; ++j)
        {
            maxx = -inf;
            dp[j-1] = -inf;
            for (int i = j; i <= n; ++i)
            {
                dp[i] = max(dp[i-1], mm[i-1]) + a[i];
                mm[i-1] = max(maxx, dp[i-1]);
                maxx = max(maxx, dp[i]);
            }
        }
        printf("%lld\n", maxx);
    }
    return 0;
}

