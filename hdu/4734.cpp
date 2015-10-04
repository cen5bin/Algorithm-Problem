#include <cstdio>
#include <cstring>
int dp[12][5000];
int digit[12];
int A, B;
void init()
{
    memset(dp, -1, sizeof(dp));
}

int dfs(int pos, int pre, bool limit)
{
    if (pos == -1) return pre >= 0 ? 1 : 0;
    if (pre < 0) return 0;
    if (!limit && dp[pos][pre] != -1) return dp[pos][pre];
    int end = limit ? digit[pos] : 9;
    int ret = 0;
    for (int i = 0; i <= end; ++i)
        ret += dfs(pos-1, pre - (1<<pos) * i, limit && i == end);
    if (!limit) dp[pos][pre] = ret;
    return ret;
}

int solve(int n)
{
    int fa = 0;
    int tmp = 1;
    while (A)
    {
        fa += A % 10 * tmp;
        A /= 10;
        tmp <<= 1;
    }
    A = fa;
    //printf("%d\n", A);
    memset(digit, 0, sizeof(digit));
    int len = 0;
    while (n)
    {
        digit[len++] = n % 10;
        n /= 10;
    }
    return dfs(len-1, A, 1);
}




int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &A, &B);
        static int cas = 1;
        printf("Case #%d: %d\n", cas++, solve(B));
    }
    return 0;
}
