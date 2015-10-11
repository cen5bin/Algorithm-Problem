#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define esp 1e-9
#define inf 0x7fffffff
#define M 55
inline int abs(int x)
{
    return x < 0 ? -x : x;
}
const int N = 1010;
typedef long long LL;
struct ball
{
    int pos;
    int cost;
}b[M][N];
int dp[M][N];
int cmp(const ball &b1, const ball &b2)
{
    return b1.pos < b2.pos;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int m, n, p;
        scanf("%d%d%d", &m, &n, &p);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &b[i][j].pos);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &b[i][j].cost);
        sort(b[0], b[0] + n, cmp);
        for (int i = 0; i < n; ++i)
            dp[0][i] = abs(p-b[0][i].pos) + b[0][i].cost;
        
        //for (int i = 0; i < n; ++i) printf("%d ", dp[0][i]);
        //puts("");

        for (int i = 1; i < m; ++i)
        {
            sort(b[i], b[i]+n, cmp);
            for (int j = 0; j < n; ++j) dp[i][j] = inf;
            int minx = inf, now = 0;
            for (int j = 0; j < n; ++j)
            {
                while (now < n && b[i-1][now].pos <= b[i][j].pos)
                    minx = min(minx, dp[i-1][now]-b[i-1][now].pos), now++;
                if (minx < inf) dp[i][j] = minx + b[i][j].pos + b[i][j].cost;
            }
            minx = inf, now = n - 1;
            for (int j = n - 1; ~j; --j)
            {
                while (~now && b[i-1][now].pos > b[i][j].pos)
                    minx = min(minx, dp[i-1][now] + b[i-1][now].pos), now--;
                if (minx < inf) dp[i][j] = min(dp[i][j], minx - b[i][j].pos + b[i][j].cost);
            }
        }
        int ans = inf;
        for (int i = 0; i < n; ++i) ans = min(ans, dp[m-1][i]);
        printf("%d\n", ans);

    }
    return 0;
}

