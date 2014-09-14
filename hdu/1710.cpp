#include <cstdio>
#include <cstring>

const int N = 1010;
struct node {
	int val;
	int lchild, rchild;
}a[N];
int cnt = 0;
int pre[N];
int in[N];
int pos[N];
int build(int s1, int s2, int l) {
	if (l==0) return -1;
	int ret = cnt++;
	a[ret].val = pre[s1];
	if (l==1) {
		a[ret].lchild = -1;
		a[ret].rchild = -1;
		return ret;
	}
	int tmp = pos[pre[s1]];
	a[ret].lchild = build(s1+1, s2, tmp-s2);
	a[ret].rchild = build(s1+tmp-s2+1, tmp+1, l - (tmp-s2)-1);
	return ret;
}
int ans[N];
int cnt1;
void postorder(int p) {
	if (a[p].lchild != -1)
		postorder(a[p].lchild);
	if (a[p].rchild != -1)
		postorder(a[p].rchild);
	ans[cnt1++] = a[p].val;
}

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		cnt = 0;
		for (int i = 0; i < n; i++)
			scanf("%d", &pre[i]);
		for (int i = 0; i < n; i++) {
			scanf("%d", &in[i]);
			pos[in[i]] = i;
		}
		cnt1 = 0;
		postorder(build(0, 0, n));
		for (int i = 0; i < cnt1; i++) {
			if (i) printf(" ");
			printf("%d", ans[i]);
		}
		puts("");
	}
	return 0;
}
