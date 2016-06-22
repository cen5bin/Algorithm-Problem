#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class DoubleWeights {
    private:
        static const int N = 22;
        int w1[N][N], w2[N][N];
        int dp[N][200][200];
        int n;
        bool used[N];
        int dfs(int x, int wei1, int wei2) {
            if (x == 1) {
                return wei1 * wei2;
            }
            int &ret = dp[x][wei1][wei2];
            if (ret != -1) return ret;
            ret = 0x7fffffff;
            used[x] = 1;
            for (int i = 0; i < n; ++i)
                if (w1[x][i] != -1 && !used[i]) {
                    ret = min(ret, dfs(i, wei1+w1[x][i], wei2+w2[x][i]));
                }
            used[x] = 0;
            return ret;
        }
    public:
        int minimalCost(vector<string> weight1, vector<string> weight2) {
            memset(w1, -1, sizeof(w1));
            memset(w2, -1, sizeof(w2));
            memset(dp, -1, sizeof(dp));
            n = weight1.size();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (weight1[i][j] != '.') w1[i][j] = weight1[i][j] - '0';
                    if (weight2[i][j] != '.') w2[i][j] = weight2[i][j] - '0';
                }
            }
            memset(used, 0, sizeof(used)); 
            int ret = dfs(0, 0, 0);
            if (ret == 0x7fffffff) ret = -1;
            return ret;
        }
}dd;

int main() {
    int n;
    while (scanf("%d", &n) ==  1) {
        vector<string> w1, w2;
        string s;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            w1.push_back(s);
        }
        for (int i = 0; i < n; ++i) {
            cin >> s;
            w2.push_back(s);
        }
        printf("%d\n", dd.minimalCost(w1, w2));
    }
    return 0;
}
