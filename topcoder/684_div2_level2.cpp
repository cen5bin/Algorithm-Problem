#include <cstdio>
class DivFreed2 {
    private:
        static const int K = 1000010;
        static const int MOD = 1e9+7;
        int sum1[K], sum2[K];

    public:
        int count(int n, int k) {
            sum1[0] = 0;
            for (int i = 1; i <= k; ++i) sum1[i] = i;
            for (int i = 1; i <= k; ++i) {
                sum2[i] = sum1[k] - sum1[i-1];
                if (sum2[i] < 0) sum2[i] += MOD;
                for (int j = i; j <= k; j+=i) {
                    sum2[i] -= (sum1[j]-sum1[j-1]);
                    if (sum2[i] < 0) sum2[i] += MOD;
                    else if (sum2[i] >= MOD) sum2[i] -= MOD;
                }
            }   
            //for (int i = 1; i <= k; ++i) printf("%d ", sum1[i]);
            //puts("");
            //for (int i = 1; i <= k; ++i) printf("%d ", sum2[i]);
            //puts("");
            for (int i = 2; i <= n; ++i) {
                for (int j = 1; j <= k; ++j) {
                    sum1[j] += sum2[j];
                    if (sum1[j] >= MOD) sum1[j] -= MOD;
                    sum1[j] += sum1[j-1];
                    if (sum1[j] >= MOD) sum1[j] -= MOD;
                }
                for (int j = 1; j <= k; ++j) {
                    sum2[j] = sum1[k] - sum1[j-1];
                    for (int t = j; t <= k; t+=j) {
                        sum2[j] -= sum1[t] - sum1[t-1];
                        if (sum2[j] < 0) sum2[j] += MOD;
                        else if (sum2[j] >= MOD) sum2[j] -= MOD;
                    }
                }
            }
            //for (int i = 1; i <= k; ++i) printf("%d ", sum1[i]);
            //puts("");
            //for (int i = 1; i <= k; ++i) printf("%d ", sum2[i]);
            //puts("");
            //int ret = 0;
            //for (int i = 1; i <= k; ++i) {
            //    ret += sum1[i];
            //    if (ret >= MOD) ret -= MOD;
            //}
            //for (int i = 1; i <= k; ++i) {
            //    ret += sum2[i];
            //    if (ret >= MOD) ret -= MOD;
            //}
            return sum1[k];
        }
} df;

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        printf("%d\n", df.count(n, k));
    }
}
