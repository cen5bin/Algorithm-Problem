#include <cstdio>
#include <cstring>

const int SIZE = 2100;
struct dessert
{
    int energy, size; 
}dd[SIZE];

struct truck
{
    int size, cost;
}tt[SIZE];
int dp[100010];
int min(int a, int b)
{
    return a < b ? a : b;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; ++i)
        {
            int t, u, v;
            scanf("%d%d%d", &t, &u, &v);
            for (int j = 1; v > 0 ; j<<=1)
            {
                if (v < j) break;
                dd[cnt1].energy = t * j;
                dd[cnt1].size = u * j;
                cnt1++;
                v -= j;
            }
            if (v)
            {
                dd[cnt1].energy = t * v;
                dd[cnt1].size = u * v;
                cnt1++;
            }
        }
        int maxv = 0;
        for (int i = 0; i < m; ++i)
        {
            int t, u, v;
            scanf("%d%d%d", &t, &u, &v);
            maxv += t * v;
            for (int j = 1; v > 0 ; j<<=1)
            {
                if (v < j) break;
                tt[cnt2].size = t * j;
                tt[cnt2].cost = u * j;
                cnt2++;
                v -= j;
            }
            if (v)
            {
                tt[cnt2].size = t * v;
                tt[cnt2].cost = u * v;
                cnt2++;
            }
        }
        if (p == 0)
        {
            puts("0");
            continue;
        }
        memset(dp, -1, sizeof(int) * (p + 10));
        dp[0] = 0;
        int cur = 0;
        int minv = 0x7fffffff;
        for (int i = 0; i < cnt1; ++i)
            for (int j = cur; j >= 0; --j)
            {
                if (dp[j] == -1) continue;
                if (j + dd[i].energy >= p) minv = min(minv, dp[j] + dd[i].size);
                else {
                    int tmp = j + dd[i].energy;
                    cur = max(cur, tmp);
                    if (dp[tmp] == -1) dp[tmp] = dp[j] + dd[i].size;
                    else
                        dp[tmp] = min(dp[tmp], dp[j] + dd[i].size);
                }
            }
        if (minv > maxv)
        {
            puts("TAT");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        int mincost = 0x7fffffff;
        cur = 0;
        for (int i = 0; i < cnt2; ++i)
            for (int j = cur; j >= 0; --j)
            {
                int tmp = j + tt[i].cost;
                if (tmp > 50000) continue;
                dp[tmp] = max(dp[tmp], dp[j] + tt[i].size);
                cur = max(cur, tmp);
                if (dp[tmp] >= minv) mincost = min(mincost, tmp);
            }
        if (mincost > 50000) puts("TAT");
        else printf("%d\n", mincost);
    }
    return 0;
}

