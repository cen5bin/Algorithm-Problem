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
#define inf 0x7fffffffffffffffLL
#define MOD 1000000007
typedef long long LL;
const int N = 50010;
struct point
{
    LL w, h;
}p[N];

int cmp(const point &p1, const point &p2)
{
    if (p1.w == p2.w) return p1.h > p2.h;
    return p1.w > p2.w;
}
LL dp[2][N];
int s[2][N];
int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k) == 2)
    {
        for (int i = 1; i <= n; ++i) scanf("%lld%lld", &p[i].w, &p[i].h);
        sort(p + 1, p+n+1, cmp);
        int cnt = 1;
        for (int i = 2; i <= n; ++i)
            if (p[i].h > p[cnt].h)
                p[++cnt] = p[i];
        int now = 0;
        for (int i = 1; i <= cnt; ++i) dp[now][i] = p[1].w * p[i].h, s[now][i] = 0;
        s[0][cnt+1] = s[1][cnt+1] = cnt - 1;
        LL ans = inf;
        ans = min(ans, dp[now][cnt]);
        for (int j = 2; j <= k; ++j)
        {
            now ^= 1;
            for (int i = cnt; i >= 1; --i)
            {
                dp[now][i] = inf;
                for (int k = s[now^1][i]; k <= s[now][i+1]; ++k)
                    if (dp[now][i] > dp[now^1][k] + p[k+1].w*p[i].h)
                    {
                        s[now][i] = k;
                        dp[now][i] = dp[now^1][k] + p[k+1].w * p[i].h;
                    }
            }
            ans = min(ans, dp[now][cnt]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

