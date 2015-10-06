#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define esp 1e-9
const int N = 1010;
struct line
{
    double x1, x2, y;
    int flag;
}p[N<<1];
vector<double> a;

int getid(double d)
{
    return lower_bound(a.begin(), a.end(), d) - a.begin() + 1;
}
int cmp(const line &l1, const line &l2)
{
    if (fabs(l1.y - l2.y) < esp) return l1.flag > l2.flag; 
    return l1.y < l2.y;
}

double len[N<<3];
int sum[N<<3];

void build(int l, int r, int rt)
{
    len[rt] = sum[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void push_down(int rt)
{
    if (sum[rt] == 0) return;
    sum[rt<<1] += sum[rt];
    sum[rt<<1|1] += sum[rt];
    sum[rt] = 0;
}

void push_up(int l, int r, int rt)
{
    if (sum[rt] >= 2)
        len[rt] = a[r] - a[l-1];
    else len[rt] = len[rt<<1] + len[rt<<1|1];
}

void update(int p, int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        sum[rt] += p;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(p, L, R, l, mid, rt<<1);
    if (R > mid) update(p, L, R, mid+1, r, rt<<1|1);
    push_up(l, r, rt);
}

double query(int l, int r, int rt)
{
    if (sum[rt] >= 2)
        return (a[r] - a[l-1]);
    if (l == r) return 0;
    push_down(rt);
    int mid = (l + r) >> 1;
    double ret = 0;
    ret += query(l, mid, rt<<1);
    ret += query(mid+1, r, rt<<1|1);
    push_up(l, r, rt);
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        a.clear();
        for (int i = 0; i < n; ++i)
        {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            p[i<<1].x1 = x1, p[i<<1].x2 = x2, p[i<<1].y = y1, p[i<<1].flag = 1;
            p[i<<1|1].x1 = x1, p[i<<1|1].x2 = x2, p[i<<1|1].y = y2, p[i<<1|1].flag = -1;
            a.push_back(x1);
            a.push_back(x2);
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        build(1, a.size(), 1);
        sort(p, p + 2 * n, cmp); 
        double now = p[0].y;
        double ans =  0;
        for (int i = 0; i < 2 * n; ++i)
        {
            double l = query(1, a.size(), 1);
            ans += l * (p[i].y - now);
            now = p[i].y;
            update(p[i].flag, getid(p[i].x1), getid(p[i].x2) - 1, 1, a.size(), 1);
        }
        printf("%.2f\n", ans + esp);
    }
    return 0;
}
