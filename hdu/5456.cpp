#include <cstdio>
#include <cstring>
const int N = 510;
typedef long long LL;
LL dp[N][2][2][2];
int need[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int NN; LL m;
LL dfs(int n, int p, int b, int c)
{
    if (n < 0) return 0;
    LL &ret = dp[n][p][b][c];
    if (ret != -1) return ret;
    ret = 0;
    if (b == 0 && c == 0)
    {
        for (int  i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
            {
                int p0 = (i + j + p) / 10;
                int x = (i + j + p) % 10;
                int nn = need[i] + need[j] + need[x];
                ret += dfs(n-nn, p0, 0, 0);
                if (i) ret += dfs(n-nn, p0, 1, 0);
                if (j) ret += dfs(n-nn, p0, 0, 1);
                if (i && j) ret += dfs(n-nn, p0, 1, 1);
                ret %= m;
            }
    }
    else if (b == 0)
    {
        for (int i = 0; i < 10; ++i)
        {
            int p0 = (i + p) / 10;
            int x = (i + p) % 10;
            int nn = need[i] + need[x];
            ret += dfs(n-nn, p0, 0, 1);
            if (i) ret += dfs(n-nn, p0, 1, 1);
            ret %= m;
        }
    }
    else if (c == 0)
    {
        for (int i = 0; i < 10; ++i)
        {
            int p0 = (i + p) / 10;
            int x = (i + p) % 10;
            int nn = need[i] + need[x];
            ret += dfs(n-nn, p0, 1, 0);
            if (i) ret += dfs(n-nn, p0, 1, 1);
            ret %= m;
        }
    }
    else 
    {
        if (p == 0 && n == 0) ret = 1;
        if (p == 1 && n == need[1]) ret = 1;
    }
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%lld", &NN, &m);
        memset(dp, -1, sizeof(dp));
        static int cas = 1;
        printf("Case #%d: %lld\n", cas++, dfs(NN-3, 0, 0, 0));
    }
    return 0;
}
