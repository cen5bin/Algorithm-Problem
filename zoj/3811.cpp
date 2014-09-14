#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 100010;
vector<int> e[N];
bool f[N];
int a[N];
int find(int x) {
	return x == a[x]?x:(a[x] = find(a[x]));
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		memset(f, 0, sizeof(f));
		for (int i = 0; i < k; i++) {
			int x;
			scanf("%d", &x);
			f[x] = 1;
		}
		for (int i = 1; i <= n; i++)
			a[i] = i;
		for (int i = 0; i < m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (f[x] || f[y]) {
				e[x].push_back(y);
				e[y].push_back(x);
				continue;
			}
			int fx = find(x);
			int fy = find(y);
			a[fx] = fy;
		}
		scanf("%d", &k);
		int pre = -1;
		bool yes = 1;
		for (int i = 0; i <k; i++) {
			int x;
			scanf("%d", &x);
			if (!yes) continue;
			f[x] = 0;
			int size = e[x].size();
			for (int j = 0; j < size; j++) 
			if (!f[e[x][j]]){
				int fx = find(x);
				int fy = find(e[x][j]);
				a[fx] = fy;
			}
			if (pre != -1) {
				int fx = find(pre);
				int fy = find(x);
				if (fx != fy) {
					yes = 0;
					continue;
				}
			}
			pre = x;
		}
		int ans = find(1);
		for (int i = 2; yes && i <= n; i++)
			if (find(i) != ans) yes = 0;
		if (yes) puts("Yes");
		else puts("No");
		for (int i = 1; i <= n; i++)
			e[i].clear();
	}
	return 0;
}
