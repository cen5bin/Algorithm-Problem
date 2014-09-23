#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
const int N = 100010;
struct point
{
	double x, y;
	point(){ x = 0; y = 0; }
	point(double x, double y) { this->x = x; this->y = y;}
	point operator -(const point &p) const {return point(this->x-p.x, this->y-p.y);}
}a[N];

int cmp(const point &p1, const point &p2)
{
	return p1.x < p2.x;
}

double cross(const point &p1, const point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

int n, q;
double q1[N], q2[N];
int stack[N];
double ans[N];
map<double, double> mm;
int main()
{
	int t;
	scanf("%d", &t);
	int cas = 0;
	const double PI = acos(-1.0);
	const double aaa = 180 / PI;
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		scanf("%d", &q);
		for (int i = 0; i < q; i++)
		{
			scanf("%lf", &q1[i]);
			q2[i] = q1[i];
		}
		sort(q2, q2+q);
		sort(a, a+n, cmp);
		int top = 0;
		stack[top++] = 0;
		int now = 1, q0 = 0;
		memset(ans, 0, sizeof(ans));
		while (now < n && q0 < q)
		{
			if (a[now].x < q2[q0])
			{
				while (top>1)
				{
					int tmp1 = stack[top-1];
					int tmp2 = stack[top-2];
					if (cross(a[tmp1]-a[now],a[tmp2]-a[now])<=0) top--;
					else break;
				}
				stack[top++] = now++;
			}
			else 
			{
				while (top>1)
				{
					int tmp1 = stack[top-1];
					int tmp2 = stack[top-2];
					point p(q2[q0], 0);
					if (cross(a[tmp1]-p, a[tmp2]-p)<=0) top--;
					else break;
				}
				int tmp = stack[top-1];
				ans[q0] = atan2(a[tmp].y, q2[q0]-a[tmp].x);
				q0++;
			}
		}
		top = 0;
		stack[top++] = n-1;
		now = n-2, q0 = q-1;
		//memset(ans, 0, sizeof(ans));
		while (now >= 0 && q0 >= 0)
		{
			if (a[now].x > q2[q0])
			{
				while (top>1)
				{
					int tmp1 = stack[top-1];
					int tmp2 = stack[top-2];
					if (cross(a[tmp1]-a[now],a[tmp2]-a[now])>=0) top--;
					else break;
				}
				stack[top++] = now--;
			}
			else 
			{
				while (top>1)
				{
					int tmp1 = stack[top-1];
					int tmp2 = stack[top-2];
					point p(q2[q0], 0);
					if (cross(a[tmp1]-p, a[tmp2]-p)>=0) top--;
					else break;
				}
				int tmp = stack[top-1];
				ans[q0] += atan2(a[tmp].y, -q2[q0]+a[tmp].x);
				q0--;
			}
		}

		printf("Case #%d:\n", ++cas);
		for (int i = 0; i < q; i++)
			mm[q2[i]] = 180-ans[i] * aaa;
		for (int i = 0; i < q; i++)
			printf("%f\n", mm[q1[i]]);
		mm.clear();
		
	}
	return 0;
}
