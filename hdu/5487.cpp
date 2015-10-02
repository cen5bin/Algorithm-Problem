#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1010;
const int M = 30;
int trans[2][N][M];
bool end1[2][N];
struct point
{
    int x, y;
    point(){}
    point(int _x, int _y):x(_x),y(_y){}
};
queue<point> q;
int state[N*N];
bool f[N][N];
char cc[N*N], ss[N*N];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k;
        memset(end1, 0, sizeof(end1));
        memset(trans, 0, sizeof(trans));
        for (int t = 0; t < 2; ++t)
        {
            scanf("%d%d%d", &n, &m, &k);
            for (int i = 0; i < k; ++i)
            {
                int x;
                scanf("%d", &x);
                x++;
                end1[t][x] = 1;
            }
            for (int i = 0; i < m; ++i)
            {
                int x, y;
                char c;
                scanf("%d%d", &x, &y);
                scanf(" %c", &c);
                x++, y++;
                trans[t][x][c-'a'] = y;
            }
        }
        memset(f, 0, sizeof(f));
        q.push(point(1, 1));
        f[0][0] = 1;
        f[1][1] = 1;
        state[1] = 0;
        int cnt1 = 0, cnt2 = 1;
        bool find = 0;
        if (end1[0][1] ^ end1[1][1])
            find = 1;
        while (!q.empty())
        {
            point p = q.front();
            q.pop();
            if (find) continue;
            cnt1++;
            for (int i = 0; i < 26; ++i)
            {
                int tx = trans[0][p.x][i];
                int ty = trans[1][p.y][i];
                if (f[tx][ty]) continue;
                cc[++cnt2] = 'a' + i;
                state[cnt2] = cnt1;
                if (end1[0][tx] ^ end1[1][ty])
                {
                    find = 1;
                    break;
                }
                f[tx][ty] = 1;
                q.push(point(tx, ty));
            }
        }
        static int cas = 1;
        printf("Case #%d: ", cas++);
        if (!find) puts("0");
        else 
        {
            int cnt = 0;
            while (cnt2 != 1)
            {
                ss[cnt++] = cc[cnt2];
                cnt2 = state[cnt2];
            }
            for (int i = cnt - 1; i >= 0; --i) putchar(ss[i]);
            puts("");
        }

    }
    return 0;
}
