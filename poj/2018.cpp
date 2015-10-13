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

const int N = 100010;
int sum[N];
int q[N];

double cal(int i, int j)
{
    return 1.0 * (sum[i] - sum[j]) / (i - j);
}

int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k) == 2)
    {
        sum[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            int x;
            scanf("%d", &x);
            sum[i] = sum[i-1] + x;
        }
        int head = 0, tail = 0;
        q[tail++] = 0;
        double ans = 0;
        for (int i = k; i <= n; ++i)
        {
            //while (head + 1 < tail && (sum[i]-sum[q[tail-1]]) * (q[tail-1] * a[tail-2]) <= (sum[q[tail-1]]-sum[q[tail-2]]) * (i - q[tail-1])) tail--;
            while (head + 1 < tail && cal(i, q[tail-1]) <= cal(q[tail-1], q[tail-2])) tail--;
            ans = max(ans, cal(i, q[tail-1]));
            int j = i - k + 1;
            while (head + 1 < tail && cal(j, q[tail-1]) <= cal(q[tail-1], q[tail-2])) tail--;
            q[tail++] = j;
        }
        printf("%d\n", (int)(ans*1000));
    }
    return 0;
}

