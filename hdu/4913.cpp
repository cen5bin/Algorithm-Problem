#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100010;
struct point
{
    LL a, b;
    int x;
}p[N];

LL exp_mod(LL a, LL b, LL c)
{
    LL ret = 1;
    while (b)
    {
        if (b & 1) ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}
const LL MOD = 1000000000+7;
int add[N<<2], cnt[N<<2];
LL sum[N<<2];

void push_down(int rt)
{
    if (add[rt] == 0) return;
    sum[rt<<1] = sum[rt<<1] * exp_mod(2, add[rt], MOD) % MOD;
    sum[rt<<1|1] = sum[rt<<1|1] * exp_mod(2, add[rt], MOD) % MOD;
    add[rt<<1] += add[rt];
    add[rt<<1|1] += add[rt];
    add[rt] = 0;
}

void push_up(int rt)
{
    sum[rt] = (sum[rt<<1] + sum[rt<<1|1]) % MOD;
    cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
}

void build(int l, int r, int rt)
{
    sum[rt] = add[rt] = cnt[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >>  1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void update1(LL v, LL a, int p, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] = (sum[rt] + v * exp_mod(2, a, MOD) % MOD ) % MOD;
        cnt[rt]++;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (p <= mid) update1(v, a, p, l, mid, rt<<1);
    else update1(v, a, p, mid+1, r, rt<<1|1);
    push_up(rt);
}

void update2(int v, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        add[rt] += v;
        sum[rt] = sum[rt] * exp_mod(2, v, MOD) % MOD;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update2(v, L, R, l, mid, rt<<1);
    if (R > mid) update2(v, L, R, mid+1, r, rt<<1|1);
    push_up(rt);
}

int query1(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    return cnt[rt];
    int mid = (l + r) >> 1;
    int ret = 0;
    if (L <= mid) ret += query1(L, R, l, mid, rt<<1);
    if (R > mid) ret += query1(L, R, mid+1, r, rt<<1|1);
    return ret;
}

LL query2(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    return sum[rt];
    push_down(rt);
    int mid = (l + r) >> 1;
    LL ret = 0;
    if (L <= mid) ret = query2(L, R, l, mid, rt<<1);
    if (R > mid)  ret = (ret + query2(L, R, mid+1, r, rt<<1|1)) % MOD;
    return ret;
}

struct node
{
    LL x;
    int id;
}pp[N];
//pair<LL, int> pp[N];
int cmp(const node & p1, const node &p2)
{
    return p1.x < p2.x;
}

int cmp2(const point &p1, const point &p2)
{
    return p1.b < p2.b;
}

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%lld%lld", &p[i].a, &p[i].b);
            pp[i].x = p[i].a;
            pp[i].id = i;
        }
        sort(pp, pp+n, cmp);
        int last = -1, cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (pp[i].x != last) cnt++;
            p[pp[i].id].x = cnt;
            last = pp[i].x;
        }
        sort(p, p+n, cmp2);
        build(1, cnt, 1);
        LL ans = 0;
        for (int i = 0; i < n; i++)
        {
            int tmp1 = query1(1, p[i].x, 1, cnt, 1);
            ans = (ans + exp_mod(2, p[i].a, MOD) *
                   exp_mod(3, p[i].b, MOD) % MOD *
                   exp_mod(2, tmp1, MOD) % MOD) % MOD;
            LL tmp2 = query2(p[i].x, cnt, 1, cnt, 1);
            ans = (ans + tmp2 * exp_mod(3, p[i].b, MOD) % MOD) % MOD;
            update1(1, p[i].a, p[i].x, 1, cnt, 1);
            update2(1, p[i].x, cnt, 1, cnt, 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
