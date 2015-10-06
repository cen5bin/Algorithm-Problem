#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1010;
vector<double> a;
#define esp 1e-9
struct line
{
    double x1, x2, y;
    int flag;
}p[N<<1];

double s[2][N<<3];
int sum[N<<3];

void build(int l, int r, int rt)
{
    s[0][rt] = s[1][rt] = 0;
    sum[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
}

void push_up(int l, int r, int rt)
{
    if (sum[rt] >= 2) s[0][rt] = s[1][rt] = a[r] - a[l-1];
    else if (sum[rt] == 1) 
    {
        s[0][rt] = a[r] - a[l-1];
        if (l != r)
            s[1][rt] = s[0][rt<<1] + s[0][rt<<1|1];
        else
            s[1][rt] = 0;
    }
    else
    {
        if (l != r)
        {
            s[0][rt] = s[0][rt<<1] + s[0][rt<<1|1];
            s[1][rt] = s[1][rt<<1] + s[1][rt<<1|1];
        }
        else s[0][rt] = s[1][rt] = 0;
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
int getid(double x)
{
    return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; 
}

int cmp(const line &l1, const line &l2)
{
    if (fabs(l1.y - l2.y) < esp) return l1.flag > l2.flag;
    return l1.y < l2.y;
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
        sort(p, p + n * 2,  cmp);
        double now = p[0].y;
        double ans = 0;
        for (int i = 0; i < 2 * n; ++i)
        {
            ans += s[1][1] * (p[i].y - now);
            now = p[i].y;
            update(p[i].flag, getid(p[i].x1), getid(p[i].x2)-1, 1, a.size(), 1);
        }
        printf("%.2f\n", ans );
    }
    return 0;
}
