#include <cstdio>
#include <cstring>
typedef long long LL;
const int M = 5 * 7 * 8 * 9;
LL dp[20][M][50];
int hash[M+10];
int digit[20];
void init()
{
    memset(hash, -1, sizeof(hash));
    int cnt = 0;
    for (int i = 1; i <= M; ++i)
        if (M % i == 0) hash[i] = cnt++;
    memset(dp, -1, sizeof(dp));
}

LL gcd(LL a, LL b)
{
    return b == 0 ? a : gcd(b, a%b);
}
LL LCM(LL a, LL b)
{
    return a / gcd(a, b) * b;
}

LL dfs(int pos, int mod, int lcm, bool limit)
{
    if (pos == -1) return (mod % lcm?0:1);
    if (!limit && dp[pos][mod][hash[lcm]] != -1) return dp[pos][mod][hash[lcm]];
    int end = limit?digit[pos]:9;
    LL ans = 0;
    for (int i = 0; i <= end; ++i)
    {
        int mod1 = (mod * 10 + i) % M;
        int lcm1 = (i==0)?lcm:LCM(lcm, i); 
        ans += dfs(pos-1, mod1, lcm1, limit && i==end);
    }
    if (!limit) dp[pos][mod][hash[lcm]] = ans;
    return ans;
}

LL solve(LL n)
{
    int len = 0;
    memset(digit, 0, sizeof(digit));
    while (n)
    {
        digit[len++] = n % 10;
        n /= 10;
    }
    return dfs(len-1, 0, 1, 1);
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
