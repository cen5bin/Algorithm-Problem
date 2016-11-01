#include <cstdio>
#include <cstring>

const int N = 25;
char s[N];

typedef long long LL;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int l = strlen(s);
        LL ret = 0x8000000000000000;
        for (int i = l - 1; i >= l - 3 && i >= 4; --i) {
            LL tmp = 0;
            int dd = 0;
            for (int j = i; j < l; ++j) dd = dd * 10 + s[j] - '0';
            //dd = dd * 10 + s[i] - '0';
            tmp -= (s[i-1] - '0') * (s[i-2] - '0') / dd;
            LL tt = 0;
            for (int j = 0; j < i - 3; ++j) tt = tt * 10 + s[j] - '0';
            tt += s[i-3] - '0';

            LL tt2 = 0;
            for (int j = 1; j <= i - 3; ++j) tt2 = tt2 * 10 + s[j] - '0';
            tt2 += s[0] - '0';
            if (tt > tt2) tmp += tt;
            else tmp += tt2;
            if (tmp > ret) ret = tmp;
        }
        static int cas = 0;
        printf("Case #%d: %lld\n", ++cas, ret);
    }
    return 0;
}
