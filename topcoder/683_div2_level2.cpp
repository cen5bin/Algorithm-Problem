#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;
#define esp 1e-9
typedef long long LL;
const int MOD = 1e9+7;


class MoveStonesEasy {
    
    int ans;
    void dfs(int now, vector<int> &a, vector<int> &b) {
        if (ans == -1) return;
        if (now == a.size() - 1) {
            if (a[now] != b[now]) ans = -1;
            return;
        }
        if (a[now] >= b[now]) {
            ans += a[now] - b[now];
            a[now + 1] += a[now] - b[now];
            dfs(now+1, a, b);
        }
        else {
            int tol = b[now] - a[now];
            for (int i = now + 1; tol && i < a.size(); i++) {
                if (a[i] <= tol) {
                    ans += a[i] * (i - now);
                    tol -= a[i];
                    a[i] = 0;
                }
                else {
                    ans += tol * (i - now);
                    a[i] -= tol;
                    tol = 0;
                }
            }
            if (tol) {
                ans = -1;
                return;
            }
            dfs(now+1, a, b);
        }
    }


    public:
        int get(vector <int> a, vector <int> b) {
            ans = 0;
            dfs(0, a, b);
            return ans;
        }
};



int main()
{
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> a, b;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            a.push_back(x);
        }
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            b.push_back(x);
        }
        MoveStonesEasy mm;
        printf("%d\n", mm.get(a, b));
    }
    return 0;
}

