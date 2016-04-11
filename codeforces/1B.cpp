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
char s[20];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        if (s[0] == 'R' && isdigit(s[1])) {
            bool flag = 0;
            for (int i = 2; s[i]; ++i)
                if (s[i] == 'C') {
                    flag = 1;
                    break;
                }
            if (flag) {
                int x = 0;
                int i;
                for (i = 1; s[i] != 'C'; ++i) x = x * 10 + s[i] - '0';
                int y = 0;
                for (++i;s[i];++i) y = y * 10 + s[i] - '0';
                char ret[10];
                int cnt = 0;
                while (y) {
                    ret[cnt] = y % 26 - 1 + 'A';
                    if (ret[cnt] < 'A') ret[cnt] = 'Z';
                    y = (y - ret[cnt] + 'A' - 1) / 26;
                    cnt++;
                }
                for (int i = cnt - 1; ~i; --i) putchar(ret[i]);
                printf("%d\n", x);
                continue;
            }
        }
        putchar('R');
        int x = 0;
        int i;
        for (i = 0; !isdigit(s[i]); ++i) x = x * 26 + s[i] - 'A' + 1;
        printf("%sC%d\n", s+i, x);
    }
    return 0;
}

