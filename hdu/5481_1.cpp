#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100010;
struct point
{
    int x, cnt;
}p[N<<1];
int cmp(const point &p1, const point &p2)
{
    if (p1.x == p2.x) return p1.cnt > p2.cnt;
    return p1.x < p2.x;
}
const LL M = 1000000007;
LL b[N]; 
int main()
{
    int T;
    scanf("%d", &T);
    b[0] = 1;
    for (int i = 1; i < N; ++i) b[i] = b[i-1] * 2 % M;
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d", &p[i<<1].x, &p[i<<1|1].x);
            p[i<<1].cnt = 1;
            p[i<<1|1].cnt = -1;
        }
        sort(p, p + n*2, cmp);
        LL ans = 0;
        int cnt = 0;
        for (int i = 0; i < 2 * n - 1; ++i)
        {
            cnt += p[i].cnt;
            int len = p[i+1].x - p[i].x;
            ans = (ans + len * (b[n] - b[n-cnt]) % M) % M;
        }
        printf("%lld\n", (ans + M) % M);
    }
    return 0;
}
