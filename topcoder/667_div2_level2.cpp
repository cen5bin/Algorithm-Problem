#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
class OrderOfOperationsDiv2 {
    private:
        static const int N = 21;
        int dp[1<<N];
        int state[1<<N];
        int calk2(int x, int y) {
            int tmp = x ^ (x & y);
            int k = 0;
            while (tmp) k++, tmp &= (tmp-1);
            return k * k;
        }

    public:
        int minTime(vector <string> s) {
            vector<int> a;
            int n = s.size();
            int m = s[0].size();
            for (int i = 0; i < n; ++i) {
                int tmp = 0;
                for (int j = 0; j < m; ++j) {
                    tmp = tmp << 1 | (s[i][j] - '0');
                }
                a.push_back(tmp);
            }
            state[0] = 0;
            for (int i = 0; i < (1<<n); ++i) {
                for (int j = 0; j < n; ++j)
                if ((i & (1<<j)) == 0) {
                    state[i|(1<<j)] = state[i] | a[j];
                }
            }
    
            
            memset(dp, -1, sizeof(dp));
            for (int i = 0; i < n; ++i) {
                dp[1<<i] = calk2(a[i], 0);
            }
            for (int i = 1; i < (1<<n); ++i)
            if (dp[i] != -1) {
                for (int k = 0; k < n; ++k) 
                if (((1<<k)&i)==0) {
                    int tmp = calk2(a[k], state[i]);
                    if (dp[i|(1<<k)] == -1 || dp[i|(1<<k)] > dp[i] + tmp)
                    dp[i|(1<<k)] = dp[i] + tmp;
                }
            }
            return dp[(1<<n)-1];
        }

};

