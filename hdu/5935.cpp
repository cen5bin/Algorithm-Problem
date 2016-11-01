#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int N = 100010;
int a[N];
typedef long long LL;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        a[0] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        int ret = 1;
        int last = 1;
        for (int i = n - 1; i >= 1; --i) {
            int t = ((a[i]-a[i-1]) * (LL)last + (a[i+1]-a[i]-1)) / (a[i+1] - a[i]);
            //printf("%d\n", t);
            ret += t;
            last = t;
        }
        static int cas = 0;
        printf("Case #%d: %d\n", ++cas, ret);
    }
    return 0;
}
