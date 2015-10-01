#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;
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

const int N = 15;
struct rec
{
    int x1, y1, x2, y2;
    int v;
}p[N];
vector<int> ax, ay;
map<int, int>mx, my, mx1, my1;

bool judge(const rec &p1, const rec &p2)
{
    if (p1.x1 >= p2.x1 && p1.x2 <= p2.x2 && p1.y1 >= p2.y1 && p1.y2 <= p2.y2) return 1;
    return 0;
}

LL dp[2][1<<N];

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int h, w, m, n;
        scanf("%d%d%d%d", &h, &w, &m, &n);
        ax.clear(); ay.clear();
        mx.clear(); my.clear();
        mx1.clear(); my1.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d%d%d%d", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2, &p[i].v);
            ax.push_back(p[i].x1); ax.push_back(p[i].x2);
            if (p[i].x2 + 1 <= h) ax.push_back(p[i].x2+1);
            ay.push_back(p[i].y1); ay.push_back(p[i].y2);
            if (p[i].y2 + 1 <= w) ay.push_back(p[i].y2 + 1);
        }
        ax.push_back(1); ax.push_back(h);
        ay.push_back(1); ay.push_back(w);
        sort(ax.begin(), ax.end());
        sort(ay.begin(), ay.end());
        ax.erase(unique(ax.begin(), ax.end()), ax.end());
        ay.erase(unique(ay.begin(), ay.end()), ay.end());
        int cntx = 0, cnty = 0;
        for (int i = 0; i < ax.size(); ++i) mx[ax[i]] = cntx, mx1[cntx++] = ax[i];
        for (int i = 0; i < ay.size(); ++i) my[ay[i]] = cnty, my1[cnty++] = ay[i];
        int now = 0;
        memset(dp, 0, sizeof(dp));
        dp[now][0] = 1;
        for (int i = 0; i < cntx; ++i)
        for (int j = 0; j < cnty; ++j)
        {
            rec p1;
            p1.x1 = mx1[i], p1.y1 = my1[j], p1.x2 = max(mx1[i+1]-1, p1.x1), p1.y2 = max(my1[j+1]-1, p1.y1);
            int maxx = m;
            for (int k = 0; k < n; ++k) if (judge(p1, p[k])) maxx = min(maxx, p[k].v);
            LL size = (p1.x2- p1.x1 + 1) * (p1.y2-p1.y1 + 1);
            LL num1 = exp_mod(maxx-1, size, M);
            LL num2 = exp_mod(maxx, size, M) - num1;
            num2 %= M;
            if (num2 < 0) num2 += M;
            //printf("%d\n", maxx);
         //   printf("%lld %lld\n", num1, num2);
            int state = 0;
            for (int k = 0; k < n; ++k) if (judge(p1, p[k]) && maxx == p[k].v) state |= 1<<k;
            //printf("%d\n", state);
            now = 1 - now;
            for (int k = 0; k < (1<<n); ++k) dp[now][k] = 0;
            for (int k = 0; k < (1<<n); ++k)
            {
                dp[now][k] = (dp[now][k] + dp[1-now][k] * num1 % M) % M;
                dp[now][k|state] = (dp[now][k|state] + dp[1-now][k] * num2 % M) % M;
            }
        }
        printf("Case #%d: %lld\n", cas, (dp[now][(1<<n)-1] + M)%M);
        //printf("Case #%d: %lld\n", cas, (dp[now][(1<<n)-1] * exp_mod(m, tol, M)  % M + M)%M);
    }
    return 0;
}
