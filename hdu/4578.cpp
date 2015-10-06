#include <cstdio>
#include <cstring>

const int N = 100010;
const int M = 10007;
int sum[3][N<<2];
int add[N<<2], multi[N<<2], w[N<<2];
void build(int l, int r, int rt)
{
    for (int i = 0; i < 3; ++i) sum[i][rt] = 0;
    add[rt] = 0;
    w[rt] = -1;
    multi[rt] = 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void mul(int rt, int p)
{
    sum[0][rt] = sum[0][rt] * p % M;
    sum[1][rt] = sum[1][rt] * p % M * p % M;
    sum[2][rt] = sum[2][rt] * p % M * p % M * p % M;
}

void add1(int l, int r, int rt, int p)
{
    int len = r - l + 1;
    sum[2][rt] = (sum[2][rt] + 3 * sum[1][rt] * p % M + 3 * p * p % M * sum[0][rt] % M + len * p % M * p % M * p % M) % M;
    sum[1][rt] = (sum[1][rt] + 2 * sum[0][rt] * p % M + len * p % M * p % M) % M;
    sum[0][rt] = (sum[0][rt] + len*p) % M;
}

void push_down(int l, int r, int rt)
{
    if (w[rt] == -1)
    {
        multi[rt<<1] = multi[rt<<1] * multi[rt] % M;
        multi[rt<<1|1] = multi[rt<<1|1] * multi[rt] % M;
        add[rt<<1] = (add[rt<<1] * multi[rt] + add[rt]) % M;
        add[rt<<1|1] = (add[rt<<1|1] * multi[rt] + add[rt]) % M;
        if (w[rt<<1] != -1) w[rt<<1] = (w[rt<<1] * multi[rt] + add[rt]) % M;
        if (w[rt<<1|1] != -1) w[rt<<1|1] = (w[rt<<1|1] * multi[rt] + add[rt]) % M;
        mul(rt<<1, multi[rt]);
        mul(rt<<1|1, multi[rt]);
        int mid = (l + r) >> 1;
        add1(l, mid, rt<<1, add[rt]);
        add1(mid+1, r, rt<<1|1, add[rt]);
    }
    else 
    {
        add[rt<<1] = add[rt<<1|1] = 0;
        multi[rt<<1] = multi[rt<<1|1] = 1;
        w[rt<<1] = w[rt<<1|1] = w[rt];
        int mid = (l + r) >> 1;
        sum[0][rt<<1] = w[rt] * (mid-l+1) % M;
        sum[1][rt<<1] = w[rt] * sum[0][rt<<1] % M;
        sum[2][rt<<1] = w[rt] * sum[1][rt<<1] % M;
        sum[0][rt<<1|1] = w[rt] * (r-mid) % M;
        sum[1][rt<<1|1] = w[rt] * sum[0][rt<<1|1] % M;
        sum[2][rt<<1|1] = w[rt] * sum[1][rt<<1|1] % M;
    }
    add[rt] = 0; multi[rt] = 1; w[rt] = -1;;
}

void push_up(int rt)
{
    for (int i = 0; i < 3; ++i)
        sum[i][rt] = (sum[i][rt<<1] + sum[i][rt<<1|1]) % M;
}

void update(int op, int p, int L, int R, int l, int r, int rt)
{
    if (l >= L && r <= R)
    {
        if (op == 1) 
        {
            add[rt] += p;
            if (add[rt] >= M) add[rt] -= M;
            if (~w[rt]) w[rt] += p;
            if (w[rt] >= M) w[rt] -= M;
            add1(l, r, rt, p);
        }
        else if (op == 2)
        {
            add[rt] = add[rt] * p % M;
            multi[rt] = multi[rt] * p % M;
            if (~w[rt]) w[rt] = w[rt] * p % M;
            mul(rt, p);
        }
        else if (op == 3)
        {
            add[rt] = 0;
            multi[rt] = 1;
            w[rt] = p % M;
            int len = r - l + 1;
            sum[0][rt] = len * p % M;
            sum[1][rt] = sum[0][rt] * p % M;
            sum[2][rt] = sum[1][rt] * p % M;
        }
        return;
    }
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(op, p, L, R, l, mid, rt<<1);
    if (R > mid) update(op, p, L, R, mid+1, r, rt<<1|1);
    push_up(rt);
}

int query(int k, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum[k][rt];
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    int ret = 0;
    if (L <= mid) ret += query(k, L, R, l, mid, rt<<1);
    if (R > mid) ret += query(k, L, R, mid+1, r, rt<<1|1);
    push_up(rt);
    return ret % M;
}

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) && (n + m))
    {
        build(1, n, 1);
        while (m--)
        {
            int k, x, y, c;
            scanf("%d%d%d%d", &k, &x, &y, &c);
            if (k != 4) update(k, c, x, y, 1, n, 1);
            else printf("%d\n", query(c-1, x, y, 1, n, 1));
        }
    }
    return 0;
}
