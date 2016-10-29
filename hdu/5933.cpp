#include <cstdio>
#include <cstring>
const int N = 100010;
typedef long long LL;
LL a[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        LL sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            sum += a[i];
        }
        static int cas = 0;
        printf("Case #%d: ", ++cas);
        if (sum % k) {
            puts("-1");
            continue;
        }
        LL p = sum / k;
        int ret = 0;
        int c = 0;
        int now = 0;
        while (now < n) {
            if (a[now] < p) {
                a[now+1] += a[now];
                now++;
                ret++;
            }
            else if (a[now] == p) now++;
            else {
                a[now] -= p;
                ret++;
                if (a[now] == 0) now++;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
