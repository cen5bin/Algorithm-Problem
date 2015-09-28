#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 32;
double dp[N][N][N*N*2];
bool f[N][N][N*N*2];
struct point
{
    int x, y, sum;
};
queue<point> qq;
int a[N][N];
int move1[2][2] = {{1, 0}, {0, 1}};
int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d", &a[i][j]);
        memset(f, 0, sizeof(f));
        point p;
        p.x = p.y = 0;
        p.sum = a[0][0];
        dp[p.x][p.y][p.sum] = 0;
        f[p.x][p.y][p.sum] = 1;
        qq.push(p);
        double ans = -1;
        while (!qq.empty())
        {
            p = qq.front();
            qq.pop();
            for (int i = 0; i < 2; ++i)
            {
                int tx = p.x + move1[i][0];
                int ty = p.y + move1[i][1];
                if (tx >= n || ty >= m) continue;
                int sum = a[tx][ty] + p.sum;
                double dd = dp[p.x][p.y][p.sum];
                double t = p.x + p.y + 1;
                double now = dd + p.sum * p.sum   / t  + 
                    a[tx][ty] * a[tx][ty] -   sum * sum / (t + 1);
                if (!f[tx][ty][sum]  || dp[tx][ty][sum] > now)
                {
                    dp[tx][ty][sum] = now;
                    f[tx][ty][sum] = 1;
                    point tmp;
                    tmp.x = tx, tmp.y = ty, tmp.sum = sum;
                    qq.push(tmp);
                }
                if (tx == n - 1 && ty == m - 1 && (ans < 0 || ans > now)) ans = now;
            }
        }
        printf("Case #%d: %.0f\n", cas, ans * (n+m-1));
    }
    return 0;
}
