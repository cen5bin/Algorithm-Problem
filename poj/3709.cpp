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
#define MOD 1000000007
typedef long long LL;
const int N = 500010;
LL dp[N];
LL sum[N];
int a[N], q[N];
LL get_up(int j, int k)
{
    return dp[j] + (LL)j * a[j+1] - sum[j] - (dp[k] + (LL)k * a[k+1] - sum[k]);
}
int get_down(int j, int k)
{
    return a[j+1] - a[k+1];
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, t;
        scanf("%d%d", &n, &t);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
        dp[0] = 0;
        int head = 0, tail = 0;
        q[tail++] = 0;
        for (int i = t; i <= n; ++i)
        {
            while (head + 1 < tail && get_up(q[head+1], q[head]) <= (LL)i * get_down(q[head+1], q[head])) head++;
            dp[i] = dp[q[head]] + sum[i] - sum[q[head]] - (i - q[head]) * (LL)a[q[head] + 1];
            int j = i - t + 1;
            if (j < t) continue;
            while (head + 1 < tail && get_up(q[tail-1], q[tail-2]) * get_down(j, q[tail-1]) >= get_up(j, q[tail-1]) * get_down(q[tail-1], q[tail-2]) ) tail--;
            q[tail++] = j;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}

