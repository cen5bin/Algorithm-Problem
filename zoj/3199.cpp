#include <cstdio>
#include <cstring>
#include <cmath>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int maxn = 50010;
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
char s[maxn];
int dp_min[maxn][17];
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void init_rmq(int n)
{
	for (int i = 1; i <= n; i++) dp_min[i][0] = height[i];
	for (int j = 1; (1<<j) <= n; j++)
	for (int i = 1; i + (1<<j) -1 <= n; i++)
		dp_min[i][j] = MIN(dp_min[i][j-1], dp_min[i+(1<<(j-1))][j-1]);
}
int rmq_query(int x, int y)
{
	int k = (int)(log(y-x+1.0)/log(2.0));
	return MIN(dp_min[x][k], dp_min[y-(1<<k)+1][k]);
}
int lcp(int x, int y)
{
	int rx = rank[x], ry = rank[y];
	if (rx > ry) rx = rx ^ ry, ry = rx ^ ry, rx = rx ^ ry;
	return rmq_query(rx+1,  ry);
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", s);
		int l = strlen(s);
		for (int i = 0; i < l; i++) r[i] = s[i] - 'a' + 1;
		r[l] = 0;
		da(r, sa, l+1, 27);
		calheight(r, sa, l);
		init_rmq(l);
		int ans = 0;
		for (int j = l / 2; !ans && j >= 1; j--)
		for (int i = 0; i + j < l; i+=j)
		{
			int k = lcp(i, i+j);
			if (k / j > 0) 
			{
				ans = j;
				break;
			}
			int aa = j - k % j;
			if (aa == j || i < aa) continue;
			if (lcp(i-aa, i-aa+j) / j > 0) 
			{
				ans = j;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
