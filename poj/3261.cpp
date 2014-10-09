#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int maxn = 1000010;
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
int rank[maxn],	height[maxn];
void calheight(int *r,int *sa,int n)
{
  int i,j,k=0;
  for(i=1;i<=n;i++) rank[sa[i]]=i;
  for(i=0;i<n;height[rank[i++]]=k)
  for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
  return;
}

int sa[maxn], r[maxn];
bool judge(int x, int n, int k)
{
	int cnt = 1;
	for (int i = 1; i <= n; i++)
		if (height[i] >= x) 
		{
			cnt++;
			if (cnt >= k) return 1;
		}
		else cnt = 1;
	return 0;
}
int main()
{
	int n, k;
	while (scanf("%d%d", &n, &k) == 2)
	{
		int m = 0;
		for (int i = 0; i < n; i++)
		{
			int x;
			scanf("%d", &x);
			x++;
			r[i] = x;
			m = MAX(m, x);
		}
		r[n] = 0;
		da(r, sa, n+1, m+1);
		calheight(r, sa, n);
		int low = 1, high = n;
		while (low < high)
		{
			int mid = (low + high + 1) >> 1;
			if (judge(mid, n, k)) low = mid;
			else high = mid - 1;
		}
		printf("%d\n", low);
	}
	return 0;
}
