#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100010;

int sum[N<<2];
void build(int l, int r, int rt)
{
    sum[rt] = r - l + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void push_up(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void update(int p, int x, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] += p;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= x) update(p, x, l, mid, rt<<1);
    else update(p, x, mid+1, r, rt<<1|1);
    push_up(rt);
}
int query(int x, int l, int r, int rt)
{
    if (sum[rt] < x) return -1;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (sum[rt<<1] >= x) return query(x, l, mid, rt<<1);
    return query(x-sum[rt<<1], mid+1, r, rt<<1|1);
}

struct node
{
    int h, k;
}p[N];

int cmp(const node &p1, const node &p2)
{
    return p1.h < p2.h;
}

int ans[N];
int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].h, &p[i].k);
        sort(p, p+n, cmp);
        build(1, n, 1);
        bool yes = 1;
        for (int i = 0; i < n; ++i)
        {
            int k = min(p[i].k, n - i - 1 - p[i].k) + 1;
            int pos = query(k, 1, n, 1);
            if (pos == -1 || k <= 0) 
            {
                yes = 0;
                break;
            }
            ans[pos] = p[i].h;
            //printf("pos: %d\n", pos);
            update(-1, pos, 1, n, 1);
        }
        printf("Case #%d:", cas);
        if (!yes)
        {
            puts(" impossible");
            continue;
        }
        for (int i = 1; i <= n; ++i) printf(" %d", ans[i]);
        puts("");
    }
    return 0;
}
