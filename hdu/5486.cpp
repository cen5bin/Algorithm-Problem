#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define MP make_pair
using namespace std;
const int N = 1000010;
typedef  pair<int, int> pii;
pair<int, int> d[N];
bool vis[N<<1];
int cntx[2];
int head[N<<1];
struct edge
{
    int v, next;
}e[N<<1];
int cmp1(const pii &p1, const pii &p2)
{
    return p1.first < p2.first;
}
int cmp2(const pii &p1, const pii &p2)
{
    return p1.second < p2.second;
}
void dfs(int x, int fa, int flag)
{
    vis[x] = 1;
    cntx[flag]++;
    for (int i = head[x]; ~i; i=e[i].next)
    {
        int v = e[i].v;
        if (v == fa || vis[v])  continue;
        dfs(v, x, flag^1);
    }
}
int cc;
void insert(int u, int v)
{
    e[cc].v = v; e[cc].next = head[u]; head[u] = cc++;
    e[cc].v = u; e[cc].next = head[v]; head[v] = cc++;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            d[i].first = x;
            d[i].second = y;
        }
        int cnt = 0;
        sort(d, d+n, cmp1);
        int now = d[0].first;
        d[0].first = cnt;
        for (int i = 1; i < n; ++i) 
        if (d[i].first != now)
        {
            now = d[i].first;
            d[i].first = ++cnt;
        }
        else d[i].first = cnt;
        sort(d, d+n, cmp2);
        now = d[0].second;
        d[0].second = ++cnt;
        for (int i = 1; i < n; ++i) 
        if (d[i].second != now)
        {
            now = d[i].second;
            d[i].second = ++cnt;
        }
        else d[i].second = cnt;
        cnt++;
        cc = 0;
        for (int i = 0; i < cnt; ++i) head[i] = -1;
        for (int i = 0; i < n; ++i)
            insert(d[i].first, d[i].second);
        for (int i = 0; i < cnt; ++i) vis[i] = 0;
        int ans[3] = {0};
        for (int i = 0; i < cnt; ++i)
            if (!vis[i]) 
            {
                cntx[0] = cntx[1] = 0;
                dfs(i, i, 0);
                if (cntx[0] == 1)
                {
                    if (cntx[1] == 1) ans[2]++;
                    else ans[0]++;
                }
                else if (cntx[1] == 1) ans[1]++;
            }
        static int cas = 1;
        printf("Case #%d:", cas++);
        for (int i = 0; i < 3; ++i) printf(" %d", ans[i]);
        puts("");
    }
    return 0;
}
