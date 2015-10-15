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
int p[N];
bool vis[N];
int cnt;
void init()
{
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < N; ++i)
    if (!vis[i])
    {
        p[cnt++] = i;
        for (int j = i * 2; j < N; j+=i) vis[i] = 1;
    }
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int g, l;
        scanf("%d%d", &g, &l);
        if (l % g)
        {
            puts("0");
            continue;
        }
        int ans = 1;
        l /= g;
        for (int i = 0; p[i] <= l / p[i]; ++i)
        {
            int cnt = 0;
            while (l % p[i] == 0) cnt++, l /= p[i];
            if (cnt) ans *= cnt * 6;
        }
        if (l > 1) ans *= 6;
        printf("%d\n", ans);
    }
    return 0;
}

