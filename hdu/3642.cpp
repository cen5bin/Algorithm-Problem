#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1010;
struct region
{
    int x1, x2, y1, y2, z1, z2;
}r[N];

struct line
{
    int x1, x2, y, z, flag;
}p[N<<1];

typedef long long LL;
int cmp(const line &l1, const line &l2)
{
    if (l1.y == l2.y) return l1.flag > l2.flag;
    return l1.y < l2.y;
}

vector<int> a;
int getid(int x)
{
    return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
}

int sum[N<<3], s[3][N<<3];
void build(int l, int r, int rt)
{
    sum[rt] = s[0][rt] = s[1][rt] = s[2][rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void push_up(int l, int r, int rt)
{
    if (sum[rt] >= 3)
    {
        for (int i = 0; i < 3; ++i)
            s[i][rt] = a[r] - a[l-1];
    }
    else if (sum[rt] == 2)
    {
        if (l != r)
        s[2][rt] = s[0][rt<<1] + s[0][rt<<1|1];
        else s[2][rt] = 0;
        for (int i = 0; i < 2; ++i)
            s[i][rt] = a[r] - a[l-1];
    }
    else if (sum[rt] == 1)
    {
        if (l != r)
        {
            s[2][rt] = s[1][rt<<1] + s[1][rt<<1|1];
            s[1][rt] = s[0][rt<<1] + s[0][rt<<1|1];
        }
        else s[1][rt] = s[2][rt] = 0;
        s[0][rt] = a[r] - a[l-1];
    }
    else 
    {
        if (l != r)
        {
            s[2][rt] = s[2][rt<<1] + s[2][rt<<1|1];
            s[1][rt] = s[1][rt<<1] + s[1][rt<<1|1];
            s[0][rt] = s[0][rt<<1] + s[0][rt<<1|1];
        }
        else s[0][rt] = s[1][rt] = s[2][rt] = 0;
    }
}

void update(int p, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        sum[rt] += p;
        push_up(l, r, rt);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) update(p, L, R, l, mid, rt<<1);
    if (R > mid) update(p, L, R, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        int minz = 0x7fffffff, maxz = -0x7fffffff;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d%d%d%d%d", &r[i].x1, &r[i].y1, &r[i].z1, &r[i].x2, &r[i].y2, &r[i].z2);
            minz = min(minz, min(r[i].z1, r[i].z2));
            maxz = max(maxz, max(r[i].z1, r[i].z2));
        }
        LL ans = 0;
        for (int t = minz; t <= maxz; ++t)
        {
            int cnt = 0;
            a.clear(); 
            for (int i = 0; i < n; ++i)
            if (r[i].z1 <= t && r[i].z2 > t)
            {
                p[cnt].x1 = p[cnt+1].x1 = r[i].x1;
                p[cnt].x2 = p[cnt+1].x2 = r[i].x2;
                p[cnt].y = r[i].y1;
                p[cnt+1].y = r[i].y2;
                p[cnt].flag = 1;
                p[cnt+1].flag = -1;
                cnt += 2;
                a.push_back(r[i].x1);
                a.push_back(r[i].x2);
            }
            if (cnt == 0) continue;
            sort(p, p+cnt, cmp);
            sort(a.begin(), a.end());
            a.erase(unique(a.begin(), a.end()), a.end());
            build(1, a.size(), 1);
            LL now = p[0].y;
            for (int i = 0; i < cnt; ++i)
            {
                ans += (p[i].y - now) * s[2][1];
                now = p[i].y;
                update(p[i].flag, getid(p[i].x1), getid(p[i].x2)-1, 1, a.size(), 1);
            }
        }
        static int cas = 1;
        printf("Case %d: %lld\n", cas++, ans);
    }
    return 0;
}
