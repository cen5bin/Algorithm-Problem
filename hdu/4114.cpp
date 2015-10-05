#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 52;
int cc[N][N];
int tt[10], ft[10], pos[10], flag[N];
int dp[1<<8][1<<8][N];
#define inf (1<<30)
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cc[i][j] = inf;
        for (int i = 1; i <= n; ++i) cc[i][i] = 0;
        for (int i = 0; i < m; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            if (cc[x][y] > z)
            cc[x][y] = cc[y][x] = z;
        }
        for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (cc[i][k] != inf && cc[k][j] != inf && cc[i][k] + cc[k][j] < cc[i][j])
                cc[i][j] = cc[i][k] + cc[k][j];

        memset(flag, 0, sizeof(flag));
        for (int i = 0; i < k; ++i)
        {
            scanf("%d%d%d", &pos[i], &tt[i], &ft[i]);
            int x;
            scanf("%d", &x);
            for (int j = 0; j < x; ++j)
            {
                int p;
                scanf("%d", &p);
                flag[p] |= (1<<i);
            }
        }
        memset(dp, -1, sizeof(dp));
        dp[0][0][1] = 0;
        for (int st1 = 0; st1 < (1<<k); ++st1)
        for (int st2 = 0; st2 < (1<<k); ++st2)
        for (int p = 1; p <= n; ++p)
        if (dp[st1][st2][p] != -1)
        {
            for (int i = 0; i < k; ++i)
            if (!(st1 & (1<<i)))
            {
                int t0 = cc[p][pos[i]] + dp[st1][st2][p];
                int st = st2 | flag[pos[i]];
                if (st & (1<<i)) t0 += ft[i];
                else t0 += tt[i];
                if (dp[st1|(1<<i)][st][pos[i]] == -1 || dp[st1|(1<<i)][st][pos[i]] > t0)
                    dp[st1|(1<<i)][st][pos[i]] = t0;
            }
            for (int i = 1; i <= n; ++i)
                {
                    int &ret = dp[st1][st2|flag[i]][i];
                    if (ret == -1 || ret > dp[st1][st2][p] + cc[p][i])
                        ret = dp[st1][st2][p] + cc[p][i];
                }
        }
        static int cas = 1;
        int ans = inf;
        for (int i = 0; i < (1<<k); ++i) 
            if (dp[(1<<k)-1][i][1] != -1)
            if (ans == -1 || ans > dp[(1<<k)-1][i][1]) ans = dp[(1<<k)-1][i][1];
        printf("Case #%d: %d\n", cas++, ans);
    }
    return 0;
}
