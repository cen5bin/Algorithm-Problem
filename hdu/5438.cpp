#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 10010;
bool vis[N];
vector<int>a[N];
int val[N];
int in[N];
queue<int> q;
LL acc;
int dfs(int x, int fa)
{
    acc += val[x];
    vis[x] = 1;
    int ret = 1;
    for (int i = 0; i < a[x].size(); ++i)
    {
        int v = a[x][i];
        if (vis[v]) continue;
        ret += dfs(v, x);
    }
    return ret;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= n; ++i) a[i].clear();
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            in[x]++;
            in[y]++;
            a[x].push_back(y);
            a[y].push_back(x);
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i)
            if (in[i] == 1) q.push(i);
            else if (in[i] == 0) vis[i] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            vis[x] = 1;
            for (int i = 0; i < a[x].size(); ++i)
            {
                int v = a[x][i];
                in[v]--;
                if (in[v] == 1) q.push(v);
            }
        }
        LL ans = 0;
        for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            acc = 0;
            int ret = dfs(i, i);
            if (ret & 1) ans += acc;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
