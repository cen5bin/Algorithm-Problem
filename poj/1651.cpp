#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N  = 110;
int dp[N][N];
int a[N];
#define inf 0x7fffffff
int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        //memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; ++i) dp[i][0] = 0;
        for (int j = 1; j < n; ++j)
        for (int i = 1; i < n; ++i)
            if (i+j-1 < n - 1)
            {
                dp[i][j] = inf;
                for (int k = i; k < i+j; ++k)
                    dp[i][j] = min(dp[i][j], dp[i][k-1-i+1] + dp[k+1][i+j-1-k] + a[k] * a[i-1] * a[i+j]);
            }
        printf("%d\n", dp[1][n-2]);
    }
    return 0;
}
