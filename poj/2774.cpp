#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
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

int main()
{
     while (scanf("%s%s", s1, s2) == 2)
	 {
		 int l1 = strlen(s1);
		 int l2 = strlen(s2);
		 for (int i = 0; i < l1; i++) r[i] = s1[i] - 'a' + 1;
		 for (int i = 0; i < l2; i++) r[i+l1] = s2[i] - 'a' + 1;
		 r[l1+l2] = 0;
		 da(r, sa, l1+l2+1, 27);
		 calheight(r, sa, l1+l2);
		 int ans = 0;
		 for (int i = 1; i <= l1 + l2; i++)
		 {
			if ((sa[i-1] >= l1 && sa[i] < l1)||(sa[i-1] < l1 && sa[i] >= l1)) ans = MAX(ans, height[i]);
		 }
		 printf("%d\n", ans);
	 }
     return 0;
}
