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

LL a[100];
LL sum[100];
int cnt;
LL cal(LL x)
{
    if (x == 0) return 0;
    int index = lower_bound(a, a+cnt, x) - a;
    if (a[index] == x) return sum[index];
    index--;
    return sum[index] + x - a[index] + cal(x - a[index] - 1);
}
int main()
{
    cnt = 0;
    sum[cnt] = 1;
    a[cnt++] = 1;
    for (; a[cnt-1] < 1e16; ++cnt) 
    {
        a[cnt] = 2 * a[cnt-1] + 1;
        sum[cnt] = 2 * sum[cnt-1] + a[cnt-1] + 1;
    }
    int T;
    scanf("%d", &T);
    while (T--) 
    {
        LL m;
        scanf("%lld", &m);
        printf("%lld\n", cal(m));
    }
    return 0;
}

