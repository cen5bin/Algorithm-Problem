#include <cstdio>
#include <cstring>

const int N = 50010;
int left[N<<2], right[N<<2];
void push_up(int l, int r, int rt)
{
	int mid = (l + r) >> 1;
	left[rt] = left[rt<<1];
	right[rt] = right[rt<<1|1];
	if (left[rt<<1] == (mid - l + 1)) left[rt] = left[rt<<1] + left[rt<<1|1];
	if (right[rt<<1|1] == (r - mid)) right[rt] = right[rt<<1|1] + right[rt<<1];
	
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		left[rt] = right[rt] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(l, r, rt);
}

void update(int v, int p, int l, int r, int rt)
{
	if (l == r)
	{
		left[rt] = right[rt] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(v, p, l, mid, rt<<1);
	else update(v, p, mid+1, r, rt<<1|1);
	push_up(l, r, rt);
}

int query(int p, int l, int r, int rt)
{
	if (l == r) return left[rt];
	if (left[rt] == r - l + 1) return left[rt];
	int mid = (l + r) >> 1;
	if (p <= mid)
	{
		if (mid-right[rt<<1]+1 <= p) return right[rt<<1] + left[rt<<1|1];
		return query(p, l, mid, rt<<1);
	}
	if (p-mid <= left[rt<<1|1]) return left[rt<<1|1] + right[rt<<1];
	return query(p, mid+1, r, rt<<1|1);
}

int stack[N];
int top;

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		build(1, n, 1);
		top = 0;
		while (m--)
		{
			char c;
			int x;
			scanf(" %c", &c);
			if (c == 'D')
			{
				scanf("%d", &x);
				stack[top++] = x;
				update(0, x, 1, n, 1);
			}
			else if (c == 'Q')
			{
				scanf("%d", &x);
				printf("%d\n", query(x, 1, n, 1));
			}
			else if (top)
				update(1, stack[--top], 1, n, 1);
		}
	}
}
