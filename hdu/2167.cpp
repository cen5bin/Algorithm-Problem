#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[100];
const int N = 17;
int a[N][N];
int dp[2][2000];
int valid[2000];
int sz, sum[N][2000];
void init(int n)
{
    sz = 0;
    for (int i = 0; i < (1<<n); ++i)
        if (!(i&(i<<1))) valid[sz++] = i;
    memset(sum, 0, sizeof(sum));
    for (int t = 0; t < n; ++t)
    for (int i = 0; i < sz; ++i)
    for (int j = 0; j < n; ++j)
    if ((1<<j)&valid[i])
    {
        sum[t][i] += a[t][j];
    }
}
int main()
{
    while (gets(s))
    {
        int tmp = 0;
        int cnt = 0;
        for (int i = 0; s[i]; ++i)
            if (s[i] == ' ') a[0][cnt++] = tmp, tmp = 0;
            else tmp = tmp * 10 + s[i] - '0';
        a[0][cnt++] = tmp;
        for (int i = 1; i < cnt; ++i)
        {
            gets(s);
            tmp = 0;
            int kk = 0;
            for (int j = 0; s[j]; ++j)
                if (s[j] == ' ') a[i][kk++] = tmp, tmp = 0;
                else tmp = tmp * 10 + s[j] - '0';
            a[i][kk++] = tmp;
        }
        gets(s);
        init(cnt);
        memset(dp, 0, sizeof(dp));
        int now = 0;
        for (int i = 0; i < sz; ++i)
            dp[now][i] = sum[0][i];
        for (int i = 0; i < cnt - 1; ++i)
        {
            for (int j = 0; j < sz; ++j)
            for (int k = 0; k < sz; ++k)
            {
                if (valid[j] & valid[k]) continue;
                if (valid[j] & (valid[k]<<1)) continue;
                if (valid[j] & (valid[k]>>1)) continue;
                dp[now^1][k] = max(dp[now^1][k], dp[now][j] + sum[i+1][k]);
            }   
            now ^= 1;
        }
        int ans = 0;
        for (int i = 0; i < sz; ++i)
            ans = max(ans, dp[now][i]);
        printf("%d\n", ans);
    }
    return 0;
}
