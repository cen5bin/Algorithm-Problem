#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define esp 1e-9
#define inf 0x7fffffff
typedef long long LL;
const int M = 10010;
const int N = 110;
int a[N][M];
int dp[N][M];
int sum[M];
inline int abs(int x)
{
    return x < 0 ? -x : x;
}
int q1[M], q2[M];
int main()
{
    int n, m, x, t;
    while (scanf("%d%d%d%d", &n, &m, &x, &t) == 4)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]);
        sum[0] = 0;
        for(int i = 1; i <= m; ++i) sum[i] = sum[i-1] +a[1][i];
        for (int i = 1; i <= m; ++i) dp[1][i] = -inf;
        for (int i = 1; i <= m; ++i)
            if (abs(i-x) <=  t)
            {
                if (i < x) dp[1][i] = sum[x] - sum[i-1];
                else dp[1][i] = sum[i] - sum[x-1];
            }
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j) dp[i][j] = -inf, sum[j] = sum[j-1] + a[i][j];
            int now = 1;
            int head = 0, tail = 0;
            for (int j = 1; j <= m; ++j)
            {
                while (head < tail && j-q2[head] > t) head++;
                while (now <= m && j >= now && j - now <= t)
                {
                    if (dp[i-1][now] == -inf)
                    {
                        now++;
                        continue;
                    }
                    while (head < tail && q1[tail-1] <= dp[i-1][now] - sum[now-1]) tail--;
                    q1[tail] = dp[i-1][now] - sum[now-1];
                    q2[tail++] = now++;
                }
                if (head < tail)
                dp[i][j] = max(dp[i][j], q1[head] + sum[j]);
            }
            head = 0, tail = 0, now = m;
            for (int j = m; j >= 1; --j)
            {
                while (head < tail && q2[head] - j > t) head++;
                while (now >= 1 && now >= j && now - j <= t)
                {
                    if (dp[i-1][now] == -inf) 
                    {
                        now--;
                        continue;
                    }
                    while (head < tail && q1[tail-1] <= dp[i-1][now] + sum[now]) tail--;
                    q1[tail] = dp[i-1][now] + sum[now];
                    q2[tail++] = now--;
                }
                if (head < tail)
                dp[i][j] = max(dp[i][j], q1[head] - sum[j-1]);
            }
            //for (int j = 1; j <= m; ++j) printf("%d ", dp[i][j]);
           // puts("");
        }
        int ans = -inf;
        for (int i = 1; i <= m; ++i)
            ans = max(ans, dp[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}

