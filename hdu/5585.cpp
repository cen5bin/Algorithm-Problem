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

char s[100];

bool judge(char *s)
{
    int x = s[strlen(s) - 1] - '0';
    if (x % 5 == 0 || x % 2 == 0) return 1;
    int acc = 0;
    for (int i = 0; s[i]; ++i) acc += s[i] - '0';
    return acc % 3 == 0;
}

int main()
{
    while (scanf("%s", s) == 1)
    {
        if (judge(s)) puts("YES");
        else puts("NO");
    }
    return 0;
}

