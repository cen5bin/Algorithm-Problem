#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 100010;
vector<int> a[N],  pri[N];
int co[N], val[N], ans[N];
bool p[N];
void init()
{
    memset(p, 0, sizeof(p));
    for (int i = 2; i < N; ++i) co[i] = 1;
    for (int i = 2; i < N; ++i)
    if (!p[i])
    {
        for (int j = i; j < N; j+=i)
        {
            p[j] = 1;
            pri[j].push_back(i);
            co[j] *= -1;
        }
    }
    vector<int> tmp;
    for (int i = 2; i < N; ++i)
    {
        for (int j = 0; j < pri[i].size(); ++j) tmp.push_back(pri[i][j]);
        pri[i].clear();
        int t = tmp.size();
        for (int j = 1; j < (1<<t); ++j)
        {
            int f = 1;
            for (int k = 0; k < t; ++k)
                if ((1<<k) & j) f *= tmp[k];
            pri[i].push_back(f);
        }
        tmp.clear();
    }
}

int num[N];
int in[N][70];
int dfs(int x, int fa)
{
    int ret = 1;
    int value = val[x];
    for (int i = 0; i < pri[value].size(); ++i) in[x][i] = num[pri[value][i]];
    for (int i = 0; i < a[x].size(); ++i)
    {
        int v = a[x][i];
        if (v == fa) continue;
        ret += dfs(v, x);
    }
    ans[x] = ret - 1;
    for (int i = 0; i < pri[value].size(); ++i)
    {
        ans[x] += num[pri[value][i]] - in[x][i];
        num[pri[value][i]] += co[pri[value][i]];
    }
    if (value == 1) ans[x]++;
    return ret;
}

int main()
{
    init();
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
        memset(num, 0, sizeof(num));
        dfs(1, 1);
        static int cas = 1;
        printf("Case #%d:", cas++);
        for (int i = 1; i <= n; ++i) printf(" %d", ans[i]);
        puts("");
        for (int i = 1; i <= n; ++i) a[i].clear();
    }
    return 0;
}
