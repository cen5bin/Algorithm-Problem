#include <cstdio>
#include <cstring>

const int N = 1000010;
int a[N];
struct point
{
	int v, id;
	point(){}
	point(int _v, int _id):v(_v), id(_id){}
}q[N];
int h, t;

int main()
{
	int n, k;
	while (scanf("%d%d", &n, &k) == 2)
	{
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		h = t = 0;
		for (int i = 0; i < n; i++)
		{
			while (h < t && q[h].id <= i - k) h++;
			while (h < t && a[i] <= q[t-1].v) t--;
			q[t++] = point(a[i], i);
			if (i >= k-1)
			{
				if (i-k+1) printf(" ");
				printf("%d", q[h].v);
			}
		}
		puts("");
		h = t = 0;
		for (int i = 0; i < n; i++)
		{
			while (h < t && q[h].id <= i - k) h++;
			while (h < t && a[i] >= q[t-1].v) t--;
			q[t++] = point(a[i], i);
			if (i >= k-1)
			{
				if (i-k+1) printf(" ");
				printf("%d", q[h].v);
			}
		}
		puts("");
	}
	return 0;
}
