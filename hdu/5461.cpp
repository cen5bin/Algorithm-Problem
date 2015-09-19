#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
priority_queue<int, vector<int>, greater<int> > pos1, neg1;
priority_queue<int> pos2, neg2;

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        int n, a1, b1;
        scanf("%d%d%d", &n, &a1, &b1);
        int zero = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            scanf("%d", &x);
            if (x == 0) zero++;
            else if (x > 0)
            {
                pos2.push(x);
                if (pos2.size() > 2)
                {
                    int tmp = pos2.top();
                    pos2.pop();
                    pos1.push(tmp);
                    if (pos1.size() > 2) pos1.pop();
                }
            }
            else 
            {
                neg2.push(x);
                if (neg2.size() > 2)
                {
                    int tmp = neg2.top();
                    neg2.pop();
                    neg1.push(tmp);
                    if (neg1.size() > 2) neg1.pop();
                }
            }
        }
        LL a[30];
        int cnt = 0;
        for (int i = 0; i < 2 && i < zero; ++i) a[cnt++] = 0;
        while (!pos1.empty()) 
        {
            a[cnt++] = pos1.top();
            pos1.pop();
        }
        while (!pos2.empty()) 
        {
            a[cnt++] = pos2.top();
            pos2.pop();
        }
        while (!neg1.empty()) 
        {
            a[cnt++] = neg1.top();
            neg1.pop();
        }
        while (!neg2.empty()) 
        {
            a[cnt++] = neg2.top();
            neg2.pop();
        }
        LL ans = a1 * a[0] * a[0] + b1 * a[1];
        for (int i = 0; i < cnt; ++i)
        for (int j = i + 1; j < cnt; ++j)
        {
            LL tmp = a1 * a[i] * a[i] + b1 * a[j];
            if (tmp > ans) ans = tmp;
            tmp = a1 * a[j] * a[j] + b1 * a[i];
            if (tmp > ans) ans = tmp;
        }
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
