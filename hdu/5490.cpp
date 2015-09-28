#include <cstdio>
#include <cstring>
typedef long long LL;
const LL MOD = 1000000007;
LL exp_mod(LL a, LL b, LL c)
{
    LL ret = 1;
    while (b)
    {
        if (b & 1)
            ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}

const int N = 10010;
LL b[N], a[N];
int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        LL b1, q, a1, d, n, m;
        scanf("%lld%lld%lld%lld%lld%lld", &b1, &q, &a1, &d, &n, &m);
        if (n == 0)
        {
            if (m == 0) printf("Case #%d: 0\n", cas);
            else printf("Case #%d: %lld\n", cas, b1 * exp_mod(q, m-1, MOD) % MOD);
        }
        else if (m == 0)printf("Case #%d: %lld\n", cas, (a1 + d * (n-1))% MOD);
        if (n*m==0) continue;
        LL tt = exp_mod(q-1, MOD-2, MOD);
        b[0] = b1;
        for (int i = 1; i <= n; ++i)
            b[i] = (b[i-1] + b[i - 1] * tt) % MOD;
        LL ans = b[n] * exp_mod(q, m - 1, MOD);
        for (int i = 1; i <= n; ++i)
        {
            a[i] = (a1 - b[i - 1] * tt) % MOD ;
            a1 += d;
        }
        LL tmp = 1;
        for (int i = n; i >= 1; --i)
        {
            ans = (ans + tmp * a[i]) % MOD;
            tmp = tmp * (n+m-i) % MOD * exp_mod(n-i+1, MOD-2, MOD) % MOD;
        }
        printf("Case #%d: %lld\n", cas, (ans + MOD) % MOD);
    }
    return 0;
}
