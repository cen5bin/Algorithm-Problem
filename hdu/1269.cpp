#include <cstdio>
#include <cstring>

struct scc_tarjan {
    static const int N = 10010;
    static const int M = 100010;
    int head[N], cnt;
    struct edge {
        int v, next;
    }e[M<<1];

    void insert(int u, int v) {
        e[cnt].v = v, e[cnt].next = head[u], head[u] = cnt++;
    }


    int dfn[N], low[N], st[N], belong[N], top, ts, bcnt;
    bool inst[N];

    void dfs(int u) {
        dfn[u] = low[u] = ++ts;
        st[++top] = u;
        inst[u] = 1;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {
                dfs(v);
                if (low[v] < low[u]) low[u] = low[v];
            }
            else if (inst[v] && low[u] > dfn[v]) {
                low[u] = dfn[v];
            }
        }
        if (low[u] == dfn[u]) {
            int v;
            bcnt++;
            do {    
                v = st[top--];
                inst[v] = 0;
                belong[v] = bcnt;
            } while(v != u); 
        }
    }

    void init() {
        cnt = ts = bcnt = 0;
        top = -1;
        memset(head, -1, sizeof(head));
        memset(inst, 0, sizeof(inst));
        memset(dfn, 0, sizeof(dfn));
        memset(belong, 0, sizeof(belong));
    }

    void solve() {
        int n, m;
        while (scanf("%d%d", &n, &m) == 2 && n + m) {
            init();
            for (int i = 0; i < m; ++i) {
                int x, y;
                scanf("%d%d", &x, &y);
                insert(x, y);
            }
            //if (n == 1) {
            //    puts("No");
            //    continue;
           // }
            dfs(1);
            bool yes = 1;
            for (int i = 1; i <= n; ++i) if (belong[i] != 1) {
                yes = 0;
                break;
            }
            if (yes) puts("Yes");
            else puts("No");
        }
    }

}scc;


int main() {
    scc.solve();
    return 0;
}
