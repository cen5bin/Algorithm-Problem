#include <cstdio>
#include <cstring>

typedef long long LL;

LL dp[20][20][2000];
int digit[20];

void init()
{
    memset(dp, -1, sizeof(dp));
}

LL dfs(int pos, int pivot, int sum, bool limit)
{
    if (pos == -1) return (sum == 0 ? 1 : 0);
    if (sum < 0) return 0;
    if (!limit && dp[pos][pivot][sum] != -1) return dp[pos][pivot][sum];
    int end = limit ? digit[pos] : 9;
    LL ret = 0;
    for (int i = 0; i <= end; ++i)
        ret += dfs(pos-1, pivot, sum+(pos-pivot)*i, limit && i == end);
    if (!limit) dp[pos][pivot][sum] = ret;
    return ret;
}

LL solve(LL n)
{
    if (n < 0) return 0;
    memset(digit, 0, sizeof(digit));
    int len = 0;
    while (n)
    {
        digit[len++] = n % 10;
        n /= 10;
    }
    LL ret = 0;
    for (int i = 0; i < len; ++i)
        ret += dfs(len-1, i, 0, 1);
    return ret - len + 1;
}


int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        LL a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", solve(b) - solve(a-1));
    }
    return 0;
}
