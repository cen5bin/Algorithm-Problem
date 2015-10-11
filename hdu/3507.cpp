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

const int N = 500010;
int q[N];
int dp[N];
int a[N], sum[N];
int get_up(int i, int j)
{
    return dp[i] + sum[i] * sum[i] - (dp[j] + sum[j] * sum[j]);
}
int get_down(int i, int j)
{
    return 2 * (sum[i] - sum[j]);  
}
int n, m;
int get_dp(int i, int j)
{
    return dp[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + m;
}
int main()
{
    while (scanf("%d%d", &n, &m) == 2)
    {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i];
        dp[0] = 0;
        int head = 0, tail = 0;
        q[tail++] = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (head + 1 < tail && get_up(q[head+1], q[head]) <= get_down(q[head+1], q[head]) * sum[i]) head++;
            dp[i] = get_dp(i, q[head]);
            while (head + 1 < tail && get_up(q[tail-1], q[tail-2]) * get_down(i, q[tail-1]) >= get_up(i, q[tail-1]) * get_down(q[tail-1], q[tail-2])) tail--;
            q[tail++] = i;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}

