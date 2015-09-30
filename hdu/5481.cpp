#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const int N = 100010;
struct node
{
    int l, r;
}p[N];

int sum[N<<3];
void build(int l, int r, int rt)
{
    sum[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void push_down(int rt)
{
    sum[rt<<1] += sum[rt];
    sum[rt<<1|1] += sum[rt];
    sum[rt] = 0;
}

void update(int p, int L, int R, int l, int r, int rt)
{
    if (l >= L && r <= R)
    {
        sum[rt] += p;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (mid >= L) update(p, L, R, l, mid, rt<<1);
    if (mid+1 <= R) update(p, L, R, mid+1, r, rt<<1|1);
}

vector<int> a;
typedef long long LL;
map<int, LL> mm, mm1;

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
LL n;
const LL M = 1000000007;
LL ans = 0;
void getans(int l, int r, int rt)
{
    if (l == r)
    {
        ans = (ans + (exp_mod(2, n, M) - exp_mod(2, n - sum[rt], M)) * (mm1[r+1]-mm1[l]) % M) % M;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    getans(l, mid, rt<<1);
    getans(mid+1, r, rt<<1|1);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        a.clear();
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            if (l == r) continue;
            p[cnt].l = l, p[cnt++].r = r;
            a.push_back(l);
            a.push_back(r);
        }
        if (n == 0)
        {
            puts("0");
            continue;
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        mm.clear();
        mm1.clear();
        int size = a.size();
        for (int i = 0; i < a.size(); ++i) {
        //    printf("%d ", a[i]);
            mm[a[i]] = i + 1, mm1[i+1] = a[i];
        }
        build(1, size, 1);
        for (int i = 0; i < cnt; ++i) 
            update(1, mm[p[i].l], mm[p[i].r]-1, 1, size, 1);
        ans = 0;
        getans(1, size, 1);
        printf("%lld\n", (ans + M) % M);
    }
    return 0;
}
