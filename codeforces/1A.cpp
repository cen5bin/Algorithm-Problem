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

int main()
{
    LL n, m, a;
    while (scanf("%lld%lld%lld", &n, &m, &a) == 3) {
        printf("%lld\n", (n+a-1)/a*((m+a-1)/a));
    }
    return 0;
}

