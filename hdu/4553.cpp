#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct node
{
    int l[2], r[2], mm[2];
    int flag[2];
}p[N<<2];

void push_up(int l, int r, int rt)
{
    int mid = (l + r) >> 1;
    for (int i = 0; i < 2; ++i)
    {
        if (p[rt<<1].l[i] == mid - l + 1) p[rt].l[i] = mid - l + 1 + p[rt<<1|1].l[i];
        else p[rt].l[i] = p[rt<<1].l[i];
        if (p[rt<<1|1].r[i] == r - mid) p[rt].r[i] = r - mid + p[rt<<1].r[i];
        else p[rt].r[i] = p[rt<<1|1].r[i];
        p[rt].mm[i] = max(p[rt<<1].mm[i], p[rt<<1|1].mm[i]);
        p[rt].mm[i] = max(p[rt].mm[i], p[rt<<1].r[i] + p[rt<<1|1].l[i]);
    }
}

void push_down(int l, int r, int rt)
{
    for (int i = 0; i < 2; ++i)
    if (p[rt].flag[i] != -1)
    {
        int mid = (l + r) >> 1;
        if (p[rt].flag[i] == 0)
        {
            p[rt<<1].l[i] = p[rt<<1].r[i] = p[rt<<1].mm[i] = mid - l + 1;
            p[rt<<1|1].l[i] = p[rt<<1|1].r[i] = p[rt<<1|1].mm[i] = r - mid;
        }
        else 
        {
            p[rt<<1].l[i] = p[rt<<1].r[i] = p[rt<<1].mm[i] = 0;
            p[rt<<1|1].l[i] = p[rt<<1|1].r[i] = p[rt<<1|1].mm[i] = 0;
        }
        p[rt<<1].flag[i] = p[rt<<1|1].flag[i] = p[rt].flag[i];
        p[rt].flag[i] = -1;
    }
}

void build(int l, int r, int rt)
{
    for (int i = 0; i < 2; ++i)
    {
        p[rt].l[i] = p[rt].r[i] = p[rt].mm[i] = r - l + 1;
        p[rt].flag[i] = -1;
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void update(int x, int flag, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (x == 0)
        {
            for (int i = 0; i < 2; ++i)
            {
                p[rt].l[i] = p[rt].r[i] = p[rt].mm[i] = r - l + 1;
                p[rt].flag[i] = 0;
            }
        }
        else 
        {
            for (int i = 0; i <= flag; ++i)
            {
                p[rt].l[i] = p[rt].r[i] = p[rt].mm[i] = 0;
                p[rt].flag[i] = 1;
            }
        }
        return;
    }
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(x, flag, L, R, l, mid, rt<<1);
    if (R > mid) update(x, flag, L, R, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
}

int query(int x, int flag, int l, int r, int rt)
{
    if (p[rt].mm[flag] < x) return 0;
    if (p[rt].l[flag] >= x) return l;
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    int ret = 0;
    if (p[rt<<1].mm[flag] >= x) ret = query(x, flag, l, mid, rt<<1);
    else if (p[rt<<1].r[flag] + p[rt<<1|1].l[flag] >= x) ret = mid - p[rt<<1].r[flag] + 1;
    else ret = query(x, flag, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
    return ret;
}
char s[20];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        static int cas = 1;
        printf("Case %d:\n", cas++);
        int n, m;
        scanf("%d%d", &n, &m);
        build(1, n, 1);
        while (m--)
        {
            int x, y;
            scanf("%s%d", s, &x);
            if (s[0] == 'D')
            {
                int ret = query(x, 0, 1, n, 1);
                if (ret)
                {
                    printf("%d,let's fly\n", ret);
                    update(1, 0, ret, ret+x-1, 1, n, 1);
                }
                else puts("fly with yourself");
            }
            else if (s[0] == 'N')
            {
                int ret = query(x, 0, 1, n, 1);
                if (ret)
                {
                    printf("%d,don't put my gezi\n", ret);
                    update(1, 1, ret, ret+x-1, 1, n, 1);
                }
                else 
                {
                    ret = query(x, 1, 1, n, 1);
                    if (ret)
                    {
                        printf("%d,don't put my gezi\n", ret);
                        update(1, 1, ret, ret+x-1, 1, n, 1);
                    }
                    else puts("wait for me");
                }
            }
            else 
            {
                scanf("%d", &y);
                update(0, 0, x, y, 1, n, 1);
                puts("I am the hope of chinese chengxuyuan!!");
            }
        }
    }
    return 0;
}
