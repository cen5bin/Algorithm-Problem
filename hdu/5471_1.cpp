#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 12;
const LL M = 1000000007;
LL exp_mod(LL a, LL b, LL c)
{
    LL ret = 1;
    while (b)
    {
        if (b & 1)
            ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}

struct rect
{
    int x1, x2, y1, y2, v;
}p[N];

vector<int> ax, ay;
map<int, int> mx1, mx2, my1, my2;
LL dp[2][1<<N];

bool judge(const rect &r1, const rect &r2)
{
    if (r1.x1 >= r2.x1 && r1.x2 <= r2.x2 && r1.y1 >= r2.y1 && r1.y2 <= r2.y2) return 1;
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int h, w, m, n;
        scanf("%d%d%d%d", &h, &w, &m, &n);
        ax.clear(); ay.clear();
        mx1.clear(); mx2.clear(); my1.clear(); my2.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d%d%d%d", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2, &p[i].v);
            ax.push_back(p[i].x1); ax.push_back(p[i].x2); if (p[i].x2 + 1 <= h) ax.push_back(p[i].x2 + 1);
            ay.push_back(p[i].y1); ay.push_back(p[i].y2); if (p[i].y2 + 1 <= h) ay.push_back(p[i].y2 + 1);
        }
        sort(ax.begin(), ax.end());
        sort(ay.begin(), ay.end());
        ax.erase(unique(ax.begin(), ax.end()), ax.end());
        ay.erase(unique(ay.begin(), ay.end()), ay.end());
        int cntx = 0, cnty = 0;
        for (int i = 0; i < ax.size(); ++i) mx1[ax[i]] = cntx, mx2[cntx++] = ax[i];
        for (int i = 0; i < ay.size(); ++i) my1[ay[i]] = cnty, my2[cnty++] = ay[i];
        int now = 0;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int tol = h * w;
        for (int i = 0; i < cntx; ++i)
        for (int j = 0; j < cnty; ++j)
        {
            rect p0;
            p0.x1 = mx2[i]; p0.y1 = my2[j]; p0.x2 = max(p0.x1, mx2[i+1]-1); p0.y2 = max(p0.y1, my2[j+1]-1);
            int maxx = m + 1;
            for (int k = 0; k < n; ++k) if (judge(p0, p[k])) maxx = min(maxx, p[k].v);
            if (maxx == m + 1) continue;
            int size = (p0.x2 - p0.x1 + 1) * (p0.y2 - p0.y1 + 1);
            tol -= size;
            LL num1 = exp_mod(maxx - 1, size, M);
            LL num2 = exp_mod(maxx, size, M) - num1;
            int state = 0;
            for (int k = 0; k < n; ++k) if (judge(p0, p[k]) && maxx == p[k].v) state |= 1<<k;
            now ^= 1;
            for (int k = 0; k < (1<<n); ++k) dp[now][k] = 0;
            for (int k = 0; k < (1<<n); ++k)
            {
                dp[now][k] = (dp[now][k] + dp[1^now][k] * num1) % M;
                dp[now][k|state] = (dp[now][k|state] + dp[1^now][k] * num2) % M;
            }
        }
        printf("Case #%d: %lld\n", cas, (dp[now][(1<<n)-1] * exp_mod(m, tol, M) % M + M) % M);
    }
    return 0;
}
