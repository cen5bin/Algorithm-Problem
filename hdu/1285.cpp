#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 510;
int in[N];
vector<int> a[N];
int ans[N];
int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= n; ++i) a[i].clear();
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            in[y]++;
            a[x].push_back(y);
        }
        priority_queue<int, vector<int>, greater<int> > q;
        for (int i = 1; i <= n; ++i) if (in[i] == 0) q.push(i);
        int cnt = 0;
        while (!q.empty())
        {   
            int x = q.top();
            q.pop();
            ans[cnt++] = x;
            for (int i = 0; i < a[x].size(); ++i)
                if (--in[a[x][i]] == 0) q.push(a[x][i]);
        }
        for (int i = 0; i < n; ++i)
        {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}
