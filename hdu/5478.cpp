#include <cstdio>
#include <cstring>

typedef long long LL;

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

int main()
{
    LL c, k1, b1, k2;
    while (scanf("%lld%lld%lld%lld", &c, &k1, &b1, &k2) == 4)
    {
        static int cas = 1;
        printf("Case #%d:\n", cas++);
        bool find = 0;
        for (int i = 1; i < c; ++i)
        {
            LL tmp = exp_mod(i, k1+b1, c);
            LL b = c - tmp;
            LL ak1 = exp_mod(i, k1, c);
            LL bk2 = exp_mod(b, k2, c);
            LL tmp1 = b;
            bool yes = 1;
            for (int j = 2; yes&&j < 5; ++j)
            {
                tmp = tmp * ak1 % c;
                tmp1 = tmp1 * bk2 % c;
                if ((tmp1+tmp)%c!=0) yes = 0;
            }
            if (yes) printf("%d %d\n", i, (int)b);
            find |= yes;
        }
        if (!find) puts("-1");
    }
    return 0;
}
