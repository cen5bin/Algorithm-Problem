#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define esp 1e-9
#define inf 0x7fffffff
#define MOD 1000000007
typedef long long LL;
const int maxn = 900010;
int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
int cmp(int *r,int a,int b,int l) {return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) ws[i]=0;
    for(i=0;i<n;i++) ws[x[i]=r[i]]++;
    for(i=1;i<m;i++) ws[i]+=ws[i-1];
    for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) ws[i]=0;
        for(i=0;i<n;i++) ws[wv[i]]++;
        for(i=1;i<m;i++) ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int rank0[maxn], height[maxn];
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rank0[sa[i]]=i;
    for(i=0;i<n;height[rank0[i++]]=k)
        for(k?k--:0,j=sa[rank0[i]-1];r[i+k]==r[j+k];k++);
    return;
}

int sa[maxn], r[maxn];
char s[210];
int flag[maxn];
bool vis[4010];
int aa[210];
int main()
{
    int n;
    while (scanf("%d", &n) == 1 && n)
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i) r[cnt++] = 26 + i;
            scanf("%s", s);
            for (int j = 0; s[j]; ++j) flag[cnt] = i, r[cnt++] = s[j] - 'a' + 1;
        }
        if (n == 1)
        {
            puts(s);
            continue;
        }
        r[cnt] = 0;
        //for (int i = 0; i <= cnt; ++i) printf("%d ", r[i]);
        //puts("");
        da(r, sa, cnt+1, 26 + n + 1);
        calheight(r, sa, cnt);
        //for (int i = 1; i <= cnt; ++i) printf("%d ", height[i]);
        //puts("");
        int low = 0, high = 200;
        int ans = -1;
        while (low < high)
        {
            int mid = (low + high + 1) >> 1;
            int xx = 0;
            bool find = 0;
            memset(vis, 0, sizeof(vis));
            for (int i = 1; !find&&i <= cnt; ++i)
            {
                if (height[i] < mid)
                {
                    if (xx)
                    {
                        memset(vis, 0, sizeof(vis));
                        xx = 0;
                    }
                }
                else 
                {
                    if (!vis[flag[sa[i-1]]]) xx++, vis[flag[sa[i-1]]] = 1;
                    if (!vis[flag[sa[i]]]) xx++, vis[flag[sa[i]]] = 1;
                    if (xx >= n)
                    {
                        ans = mid;
                        for (int j = sa[i-1]; j < sa[i-1] + ans; ++j) aa[j-sa[i-1]] = r[j];
                        find = 1;
                    }
                }
            }
            if (find) low = mid;
            else high = mid - 1;
        }
        if (ans != -1) 
        {
            for (int i = 0; i < ans; ++i) printf("%c", aa[i]-1+'a');
            puts("");
        }
        else puts("IDENTITY LOST");
    }
    return 0;
}

