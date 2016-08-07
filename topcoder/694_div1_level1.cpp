#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
class TrySail {
    public:
        int get(vector<int> strength) {
            bool f[256][256][2];
            memset(f, 0, sizeof(f));
            int all = 0;
            int flag = 0;
            f[0][0][0] = 1;
            for (int x : strength) {
                for (int i = 0; i < 256; ++i)
                for (int j = 0; j < 256; ++j)
                if (f[i][j][flag]) {
                    f[i^x][j][flag ^ 1] = 1;
                    f[i][j ^ x][flag ^ 1] = 1;
                    f[i][j][flag ^ 1] = 1;
                }
                flag ^= 1;
                all ^= x;
            }
            int ret = 0;
            for (int i = 0; i < 256; ++i)
            for (int j = 0; j < 256; ++j)
            if (f[i][j][flag]) {
                ret = max(ret, i + j + (all ^ i ^ j));
            }
            return ret;
        }
};
