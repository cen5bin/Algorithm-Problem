#include <cstdio>
#include <cstring>
#include <cmath>
#define PI acos(-1.0)
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int x[3], y[3];
        for (int i = 0; i < 3; ++i) scanf("%d%d", &x[i], &y[i]);
        double AB2 = (x[1]-x[0]) * (x[1]-x[0]) + (y[1]-y[0]) * (y[1] - y[0]);
        double AB = sqrt(AB2);
        double BC2 = (x[1]-x[2])*(x[1]-x[2]) + (y[1]-y[2])*(y[1]-y[2]);
        double BC = sqrt(BC2);
        double h2 = (AB2 - BC2/4);
        double h = sqrt(h2);
        double an = PI - acos((AB2*2-BC2)/(2*AB2));
        double r = sqrt(BC2/4/h2*AB2);
        double ans = an * r + h;
        static int cas = 1;
        printf("Case #%d: %.4f\n", cas++, ans);
    }
    return 0;
}
