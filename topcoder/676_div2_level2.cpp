#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

class BoardEscapeDiv2 {
    private:
        static const int K = 110;
        static const int N = 55;
        static int move[4][2];
        //static const int move[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        int dp[K][N][N];
        bool dfs(int k, int r, int c, const vector<string> &s) {
            if (s[r][c] == 'E' || k == 0) return 0;
            int &ret = dp[k][r][c];
            if (ret != -1) return ret;
            ret = 0;
            for (int i = 0; i < 4; ++i) {
                int tr = r + move[i][0];
                int tc = c + move[i][1];
                if (tr >= 0 && tr < s.size() && tc >= 0 && tc < s[0].size() && s[tr][tc] != '#') ret |= !dfs(k-1, tr, tc, s);
                if (ret) return ret;
            }
            return ret;
        }

    public:
        string findWinner(vector<string> s, int k) {
            memset(dp, -1, sizeof(dp));
            for (int i = 0; i < s.size(); ++i)
                for (int j = 0; j < s[i].size(); ++j)
                    if (s[i][j] == 'T') {
                        return dfs(k, i, j, s) ? "Alice" : "Bob";
                    }
            return "Alice";
        }
};

int BoardEscapeDiv2::move[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

int main() {
    int n;
    return 0;
}
