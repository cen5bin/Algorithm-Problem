#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef long long LL;
const int maxn = 200010;
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
int rank[maxn],     height[maxn];
void calheight(int *r,int *sa,int n)
{
  int i,j,k=0;
  for(i=1;i<=n;i++) rank[sa[i]]=i;
  for(i=0;i<n;height[rank[i++]]=k)
  for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
  return;
}

int sa[maxn], r[maxn];
char s1[maxn], s2[maxn];
bool vis[maxn];
LL stack[maxn], flag[maxn], top, sum[2], cnt[maxn][2];
int main()
{
     int k;
     while (scanf("%d", &k) == 1 && k)
     {
         scanf("%s%s", s1, s2);
         int l1 = strlen(s1);
		 int l2 = strlen(s2);
         for (int i = 0; i < l1; i++) r[i] = s1[i] - '\0';
         r[l1] = 128;
         for (int i = 0; i < l2; i++) r[i+l1+1] = s2[i] - '\0';
         r[l1+l2+1] = 0;
         da(r, sa, l1+l2+2, 129);
		 //for (int i = 1; i <= l1 + l2 + 1; i++)
		 //{
		 //    if (sa[i] < l1) printf("1: ");
		 //    else if (sa[i] > l1) printf("2: ");
		 //    for (int j = sa[i]; j < l1+l2+1; j++) printf("%c", r[j]);
		 //    puts("");
		 //}
         calheight(r, sa, l1+l2+1);
         LL ans = 0;
         top = 0;
         sum[0] = sum[1] = 0;
         for (int i = 1; i <= l1 + l2 + 1; i++)
         {
             if (height[i] < k)
             {
                 top = sum[0] = sum[1] = 0;
				 cnt[0][0] = cnt[0][1] = 0;
                 continue;
             }
			 int ff = 1;
			 if (sa[i-1] < l1) ff = 0;
			 stack[top] = height[i]-k+1;
			 cnt[top][ff] = 1;
			 cnt[top++][1-ff] = 0;
			 sum[ff] += height[i]-k+1;
			 while (top > 1 && stack[top-2] >= stack[top-1])
			 {
				 sum[0] += (stack[top-1]-stack[top-2])*cnt[top-2][0];
				 sum[1] += (stack[top-1]-stack[top-2])*cnt[top-2][1];
				 stack[top-2] = stack[top-1];
				 cnt[top-2][0] += cnt[top-1][0];
				 cnt[top-2][1] += cnt[top-1][1];
				// sum[flag[top-1]] += height[i] - k + 1 - stack[top-1];
				 top--;
			 }
			 //stack[top] = height[i] - k + 1;
			// if (sa[i-1] < l1) flag[top] = 0, sum[0] += height[i] - k + 1;
			// else if (sa[i-1] > l1)flag[top] = 1, sum[1] += height[i] - k + 1;
			// top++;
			 if (sa[i] < l1) ans += sum[1];
			 else if (sa[i] > l1)ans += sum[0];
         }
         printf("%lld\n", ans);
     }
     return 0;
}
