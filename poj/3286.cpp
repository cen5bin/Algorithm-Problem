#include <cstdio>
#include <cstring>
typedef long long LL;
LL cal(LL x)
{
    if (x < 0) return 0;
    if (x < 10) return 1;
    int a[20] = {0};
    int cnt = 0;
    LL tmp1 = x;
    while (tmp1)
    {
        a[cnt++] = tmp1 % 10;
        tmp1 /= 10;
    }
    tmp1 = x / 10;
    LL ret = tmp1 + 1;
    LL tmp2 = 0;
    LL l = 1;
    for (int i = 1; i < cnt - 1; ++i)
    {
        tmp1 /= 10;
        tmp2 += l * a[i-1];
        l *= 10;
        if (a[i] > 0) ret += tmp1 * l;
        else ret += (tmp1 - 1) * l + tmp2 + 1;
    }
    return ret;
}
int main()
{
    //for (int i = 100; i <= 200; ++i)
    //    printf("%d: %lld\n", i, cal(i));
    LL m, n;
    while (scanf("%lld%lld", &m, &n) && m >= 0 && n >= 0)
    {
        printf("%lld\n", cal(n) - cal(m-1));
    }
    return 0;
}
