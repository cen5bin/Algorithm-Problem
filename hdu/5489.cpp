#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 100010;
int a[N];
int r[N];
int dp[N];
int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int n, l;
        scanf("%d%d", &n, &l);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        r[0] = a[0];
        int maxx = 1;
        dp[l] = 1;
        int ans = 0;
        for (int i = 0; i + l + 1<= n; ++i)
        {
            int index = lower_bound(r, r+maxx, a[i]) - r;
            r[index] = a[i];
            maxx = max(maxx, index+1);
            ans = max(maxx, ans);
            index = lower_bound(r, r+maxx, a[i+l+1]) - r;
            dp[i+l+1] = index + 1;
        }
        maxx = 1;
        r[0] = -a[n-1];
        for (int i = n - 1; i >= l; --i)
        {
            int index = lower_bound(r, r+maxx, -a[i]) - r;
          //  printf("%d ", index+1);
            r[index] = -a[i];
            maxx = max(maxx, index+1);
            ans = max(ans, index + dp[i]);
        }
        //puts("");
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}

