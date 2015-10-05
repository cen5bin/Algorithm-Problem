#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 17;
char s[N][110];
int d[N], c[N];
int dp1[1<<N], dp2[1<<N];
int path[1<<N];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%s%d%d", s[i], &d[i], &c[i]);
        memset(dp1, -1, sizeof(dp1));
        memset(dp2, -1, sizeof(dp2));
        dp1[0] = dp2[0] = 0;
        for (int i = 0; i < (1<<n); ++i)
        {
            for (int j = 0; j < n; ++j)
            if (!((1<<j)&i))
            {
                dp1[i|(1<<j)] = dp1[i] + c[j];
                int tmp = dp2[i] + max(dp1[i|(1<<j)]-d[j], 0);
                if (dp2[i|(1<<j)] == -1 || dp2[i|(1<<j)] > tmp)
                    dp2[i|(1<<j)] = tmp, path[i|(1<<j)] = j;
            }
        }
        printf("%d\n", dp2[(1<<n)-1]);
        int now = (1<<n) - 1;
        int ans[N];
        int cnt = 0;
        while (now)
        {
            ans[cnt++] = path[now];
            now ^= 1<<path[now];
        }
        for (int i = cnt - 1; ~i; --i) puts(s[ans[i]]);
    }
    return 0;
}
