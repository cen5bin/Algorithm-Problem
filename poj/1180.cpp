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
const int N = 10010;
int dp[N];
int sumt[N], sumf[N];
int q[N];
int get_up(int i, int j)
{
    return dp[i] - dp[j];
}
int get_down(int i, int j)
{
    return sumt[i] - sumt[j];
}
int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        int s;
        scanf("%d", &s);
        for (int i = 1; i <= n; ++i) scanf("%d%d", &sumt[i], &sumf[i]);
        for (int i = n - 1; i >= 1; --i) sumt[i] += sumt[i+1], sumf[i] += sumf[i+1];
        int head = 0, tail = 0;
        q[tail++] = n + 1;
        dp[n+1] = sumt[n+1] = sumf[n+1] = 0;
        for (int i = n; i >= 1; --i)
        {
            while (head + 1 < tail && get_up(q[head+1], q[head]) <= (LL)sumf[i] * get_down(q[head+1], q[head])) head++;
            dp[i] = dp[q[head]] + (s + sumt[i]-sumt[q[head]]) * sumf[i];
            while (head + 1 < tail && get_up(q[tail-1], q[tail-2]) * (LL)get_down(i, q[tail-1]) >= (LL)get_up(i, q[tail-1]) * get_down(q[tail-1], q[tail-2])) tail--;
            q[tail++] = i;
        }
        printf("%d\n", dp[1]);
    }
    return 0;
}

