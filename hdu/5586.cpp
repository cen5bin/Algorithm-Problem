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

const int N = 100010;
int a[N];

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        int sum = 0;
        for (int i = 0; i < n; ++i) 
        {
            scanf("%d", &a[i]);
            sum += a[i];
            a[i] = (a[i] * 1890 + 143) % 10007 - a[i];
        }
        int acc = 0, tmp = 0;
        for (int i = 0; i < n; ++i)
        {
            acc += a[i];
            if (acc < 0) acc = 0;
            tmp = max(tmp, acc);
        }
        printf("%d\n", sum + tmp);
    }
    return 0;
}

