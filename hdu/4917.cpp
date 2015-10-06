#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 45;
int cc[N][N];
const int M = 1e9+7;
vector<int> a[N];
int in[N];
int dp[1<<21];
int v[25], tol;
int p[N];
int find(int x)
{
    return x == p[x] ? x : p[x] = find(p[x]);
}

int cal(int state)
{
    int ret = 0;
    while (state) ret++, state&=(state-1);
    return ret;
}

int dfs(int state)
{
    if (cal(state) == 1) return 1;
    if (dp[state] != -1) return dp[state];
    int ret = 0;
    for (int i = 0; i < tol; ++i)
    if (in[v[i]] == 0 && (state&(1<<i)) )
    {
        for (int j = 0; j < a[v[i]].size(); ++j)
            in[a[v[i]][j]]--;
        ret += dfs(state ^ (1<<i));
        if (ret >= M) ret -= M;
        for (int j = 0; j < a[v[i]].size(); ++j)
            in[a[v[i]][j]]++;
    }
    dp[state] = ret;
    return ret;
}

typedef long long LL;
int fac[N];
int main()
{
    for (int i = 1; i < N; ++i) cc[i][0] = cc[i][i] = 1;
    for (int i = 2; i < N; ++i)
    for (int j = 1; j < i; ++j)
        cc[i][j] = (cc[i-1][j-1] + cc[i-1][j]) % M;
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i-1] * (LL)i % M;
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= n; ++i) a[i].clear();
        for (int i = 1; i <= n; ++i) p[i] = i;
        while (m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            in[y]++;
            a[x].push_back(y);
            p[find(y)] = find(x);
        }
        int ans = 1;
        int now = n;
        for (int i = 1; now && i <= n; ++i)
        {
            int cnt = 0;
            for (int j = 1; j <= n; ++j)
                if (find(j) == i)
                    v[cnt++] = j;
            if (cnt == 0) continue;
            for (int j = 1; j < (1<<cnt); ++j) dp[j] = -1;
            tol = cnt;
            ans = (LL)ans * dfs((1<<tol)-1) % M * cc[now][cnt] % M;
            now -= cnt;
        }
        printf("%d\n", (int)(ans * (LL)fac[now] % M)); 
    }
    return 0;
}
