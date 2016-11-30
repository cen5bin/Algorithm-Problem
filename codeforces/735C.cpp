#include <cstdio>
#include <cstring>

typedef long long LL;

const int N = 1000;
LL a[N];

int main() {
    a[0] = 1;
    a[1] = 2;
    int tmp = 0; 
    for (int i = 2; ; ++i) {
        a[i] = a[i-1] + a[i-2];
        if (a[i] < a[i-1]) {
            tmp = i - 1;
            break;
        }
    }
    LL n;
    //while (scanf("%lld", &n) == 1) {
    while (scanf("%I64d", &n) == 1) {
        int low = 0, high = tmp;
        while (low < high) {
            int mid = (low + high + 1) >> 1;
            if (a[mid] > n) high = mid - 1;
            else low = mid;
        } 
        printf("%d\n", low);
    }
    return 0;
}
