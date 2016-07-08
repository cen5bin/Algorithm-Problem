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



class ABBA {
    public:
        string canObtain(string initial, string target) {
            int end = target.length() - 1;
            int start = 0;
            int flag = 1;
            while (end - start + 1 > initial.length()) {
                if (flag == 1)  {
                    if (target[end] == 'B') flag = 0;
                    end--;
                }
                else {
                    if (target[start] == 'B') flag = 1;
                    start++;
                }
            }
            if (end - start + 1 < initial.length()) return "Impossible";
            if (flag == 1) {
                for (int i = start; i <= end; ++i) if (target[i] != initial[i-start]) return "Impossible";
            }
            else {
                for (int i = end; i >= start; --i) if (target[i] != initial[end-i]) return "Impossible";
            }
            return "Possible";
        }
};


int main()
{
    string s1, s2;
    while (cin >> s1 >> s2) {
        ABBA abba;
        cout << abba.canObtain(s1, s2) << endl;
    }
    return 0;
}

