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
int dp[N][N];
int a[N], b[N];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= m; ++i)
            scanf("%d", &b[i]);
        dp[0][1] = dp[1][0] = 0;
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if (a[i] == b[j]) continue;
            int k1, k2;
            for (k1=j-1; k1; --k1) if (b[k1] == a[i]) break;
            if (k1 == 0) continue;
            for (k2=i-1; k2; --k2) if (a[k2] == b[j]) break;
            if (k2 == 0) continue;
            dp[i][j] = max(dp[i][j], dp[k2-1][k1-1]+2);
        }
        printf("%d\n", dp[n][m]);
    }
    return 0;
}

