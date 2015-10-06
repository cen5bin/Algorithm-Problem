#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

map<string, int> mm;
char s1[12], s2[12];
const int N = 18;
vector<int> a[N];
int in[N];
int dp[1<<N];
int n, tol;
int cal(int state)
{
    int ret = 0;
    while (state) ret++, state &= (state-1);
    return ret;
}
int dfs(int state)
{
    if (cal(state) == 1) return 1;
    if (dp[state] != -1) return dp[state];
    int ret = 0;
    for (int i = 0; i < tol; ++i)
    if (in[i+1] == 0 && ((1<<i) & state))
    {
        for (int j = 0; j < a[i+1].size(); ++j)
            in[a[i+1][j]]--;
        ret += dfs(state ^ (1<<i));
        for (int j = 0; j < a[i+1].size(); ++j)
            in[a[i+1][j]]++;
    }
    dp[state] = ret;
    return ret;
}

int main()
{
    while (scanf("%d", &n) == 1)
    {
        int cnt = 0;
        mm.clear();
        memset(in, 0, sizeof(in));
        while (n--)
        {
            scanf("%s%s", s1, s2);
            if (mm[s1] == 0) mm[s1] = ++cnt;
            if (mm[s2] == 0) mm[s2] = ++cnt;
            in[mm[s2]]++;
            a[mm[s1]].push_back(mm[s2]);
        }
        tol = cnt;
        memset(dp, -1, sizeof(dp));
        int ret = dfs((1<<tol) - 1);
        printf("%d\n", ret);
        for (int i = 1; i <= tol; ++i) a[i].clear();
    }
    return 0;
}
