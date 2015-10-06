#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;
struct node
{
    int l, r, mm, flag;
}p[N<<2];

void push_up(int l, int r, int rt)
{
    int mid = (l + r) >> 1;
    if (p[rt<<1].l == mid - l + 1) p[rt].l = mid - l + 1 + p[rt<<1|1].l;
    else p[rt].l = p[rt<<1].l;
    if (p[rt<<1|1].r == r - mid) p[rt].r = r - mid + p[rt<<1].r;
    else p[rt].r = p[rt<<1|1].r;
    p[rt].mm = max(p[rt<<1].mm, p[rt<<1|1].mm);
    p[rt].mm = max(p[rt].mm, p[rt<<1].r + p[rt<<1|1].l);
}

void push_down(int l, int r, int rt)
{
    if (p[rt].flag == -1) return;
    if (p[rt].flag == 1)
        p[rt<<1].l = p[rt<<1].r = p[rt<<1].mm = p[rt<<1|1].l = p[rt<<1|1].r = p[rt<<1|1].mm = 0;
    else 
    {
        int mid = (r + l) >> 1;
        p[rt<<1].l = p[rt<<1].r = p[rt<<1].mm = mid - l + 1;
        p[rt<<1|1].l = p[rt<<1|1].r = p[rt<<1|1].mm = r - mid;
    }
    p[rt<<1].flag = p[rt<<1|1].flag = p[rt].flag;
    p[rt].flag = -1;
}

void build(int l, int r, int rt)
{
    p[rt].l = p[rt].r = p[rt].mm = r - l + 1;
    p[rt].flag = -1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void update(int x, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (x == 1)
            p[rt].l = p[rt].r = p[rt].mm = 0;
        else p[rt].l = p[rt].r = p[rt].mm = r - l + 1;
        p[rt].flag = x;
        return;
    }
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(x, L, R, l, mid, rt<<1);
    if (R > mid) update(x, L, R, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
}

int query(int x, int l, int r, int rt)
{
    if (p[rt].mm < x) return 0;
    if (p[rt].l >= x) return l;
    int mid = (l + r) >> 1;
    push_down(l, r, rt);
    int ret = 0;
    if (p[rt<<1].mm >= x)  ret = query(x, l, mid, rt<<1);
    else if (p[rt<<1].r + p[rt<<1|1].l >= x) ret = mid - p[rt<<1].r + 1;
    else ret = query(x, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
    return ret;
}

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        build(1, n, 1);
        while (m--)
        {
            int op, x, y;
            scanf("%d", &op);
            if (op == 1)
            {
                scanf("%d", &x);
                int ret = query(x, 1, n, 1);
                printf("%d\n", ret);
                if (ret)
                update(1, ret, ret+x-1, 1, n, 1);
//                printf("asd: %d %d %d\n", p[1].l, p[1].r, p[1].mm);
            }
            else 
            {
                scanf("%d%d", &x, &y);
                update(0, x, x+y-1, 1, n, 1);
            }
        }
    }
    return 0;
}
