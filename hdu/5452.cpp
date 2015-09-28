#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct LCA {
    static const int N = 20010; //点数
    static const int M = 200010; //边数
    int head[N];
    struct edge {
        int u, v, l, next;
    } e[M<<1];  //无向，需乘以2
    int cnt;  //累计边的下标
    void init() {
        cnt = ts = 0;
        memset(head, -1, sizeof(head));
        memset(acc, 0, sizeof(acc));
        ans = 0x7fffffff;
    }
    void insert(int u, int v, int l = 1) {
        e[cnt].u = u, e[cnt].v = v, e[cnt].l = l, e[cnt].next = head[u], head[u] = cnt++;
        swap(u, v);
        e[cnt].u = u, e[cnt].v = v, e[cnt].l = l, e[cnt].next = head[u], head[u] = cnt++;
    }
    int deep[N], list[M<<2], first[N], ts;
    void dfs(int u, int fa, int d) {
        ts++;
        first[u] = ts, deep[u] = d, list[ts] = u;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            dfs(v, u, d+e[i].l);
            list[ts] = u;
        }
    }
    static const int MM = 20; //这里1 << MM 必须大于 M<<2
    int dp[M<<2][MM];
    int bb[MM + 10];
    void init_rmq() {
        for (int i = 0; i <= MM; ++i) bb[i] = 1 << i;
        for (int i = 1; i <= ts; ++i) dp[i][0] = list[i];
        for (int j = 1; j < MM; ++j) 
            for (int i = 1; i + bb[j] - 1 <= ts; ++i)
                if (deep[dp[i][j-1]] < deep[dp[i+bb[j-1]][j-1]])
                    dp[i][j] = dp[i][j-1];
                else dp[i][j] = dp[i+bb[j-1]][j-1];
    }
    void cal(int root) {
        dfs(root, root, 0);
        init_rmq();
    }
    int query(int u, int v) {
        int fu = first[u], fv = first[v];
        if (fu > fv) swap(fu, fv);
        int len = fv - fu + 1;
        int k = lower_bound(bb, bb+MM+1, len) - bb;
        if (k) k--;
        if (deep[dp[fu][k]] > deep[dp[fv-bb[k]+1][k]]) return dp[fv-bb[k]+1][k];
        return dp[fu][k];
    }
    int acc[N];
    int ans;
    int dfs1(int x, int fa)
    {
        int ret = acc[x];
        for (int i = head[x]; ~i; i = e[i].next)
        {
            int v = e[i].v;
            if (v == fa) continue;
            int tmp = dfs1(v, x);
            ans = min(ans, tmp);
            ret += tmp;
        }
        return ret;
    }
}lca;

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        lca.init();
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            lca.insert(x, y);
        }
        lca.cal(1);
        for (int i = 0; i < m - n + 1; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            lca.acc[x]++;
            lca.acc[y]++;
            lca.acc[lca.query(x, y)] -= 2;
        }
        lca.dfs1(1, 1);
        printf("Case #%d: %d\n", cas, lca.ans + 1);
    }
    return 0;
}
