#include <cstdio>
#include <cstring>
const int N = 1010;
int map[N][N];
int link[N];
bool vis[N];
int n;
int find(int x) {
    for (int i = 1; i <= n; ++i) {
        if (map[x][i] && !vis[i]) {
            vis[i] = 1;
            if (link[i] == -1 || find(link[i])) {
                link[i] = x;
                return 1;
            }
        }
    }
    return 0;
}

int hungary() {
    int ret = 0;
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (find(i)) ret++;
    }
    return ret / 2;
}


int main() {
    int k;
    while (scanf("%d%d", &n, &k) == 2) {
        memset(map, 0, sizeof(map));
        for (int i = 0; i < k; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            map[x][n+y] = map[n+y][x] = 1;
        }
        n = n << 1;
        printf("%d\n", hungary());
    }
    return 0;
}
