#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int maxn = 110010;
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
int xx[15][2], xx1[15], tt[maxn];
bool judge(int x, int l, int n)
{
	memset(xx, -1, sizeof(xx));
	memset(xx1, 0, sizeof(xx1));
	int cnt = 0;
	for (int i = 1; i <= l; i++)
	{
		if (height[i] < x)
		{
			memset(xx, -1, sizeof(xx));
			memset(xx1, 0, sizeof(xx1));
			cnt = 0;
			continue;
		}
		if (xx[tt[sa[i-1]]][0] == -1)
		{
			xx[tt[sa[i-1]]][0] = xx[tt[sa[i-1]]][1] = sa[i-1];
			xx1[tt[sa[i-1]]]++;
		}
		else if (xx1[tt[sa[i-1]]] < 2)
		{
			if (xx[tt[sa[i-1]]][0] + x <= sa[i-1]) xx1[tt[sa[i-1]]]++;
			if (xx[tt[sa[i-1]]][0] > sa[i-1]) xx[tt[sa[i-1]]][0] = sa[i-1];
			if (sa[i-1] + x <= xx[tt[sa[i-1]]][1]) xx1[tt[sa[i-1]]]++;
			if (sa[i-1] > xx[tt[sa[i-1]]][1]) xx[tt[sa[i-1]]][1] = sa[i-1];
			if (xx1[tt[sa[i-1]]] >= 2) cnt++;
		}
		if (xx[tt[sa[i]]][0] == -1)
		{
			xx[tt[sa[i]]][0] = xx[tt[sa[i]]][1] = sa[i];
			xx1[tt[sa[i]]]++;
		}
		else if (xx1[tt[sa[i]]] < 2)
		{
			if (xx[tt[sa[i]]][0] + x <= sa[i]) xx1[tt[sa[i]]]++;
			if (xx[tt[sa[i]]][0] > sa[i]) xx[tt[sa[i]]][0] = sa[i];
			if (sa[i] + x <= xx[tt[sa[i]]][1]) xx1[tt[sa[i]]]++;
			if (sa[i] > xx[tt[sa[i]]][1]) xx[tt[sa[i]]][1] = sa[i];
			if (xx1[tt[sa[i]]] >= 2) cnt++;
		}
		if (cnt >= n) return 1;
	}
	return 0;
}
int main()
{
	int n;
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		int l = 0;
		int maxl = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s);
			for (int j = 0; s[j]; j++) r[l] = s[j] - 'a' + 1, tt[l++] = i;
			r[l++] = 27 + i;
			maxl = MAX(maxl, strlen(s));
		}
		r[l] = 0;
		da(r, sa, l+1, n+27);
		calheight(r, sa, l);
		int low = 0, high = maxl;
		while (low < high)
		{
			int mid = (low + high + 1) >> 1;
			if (judge(mid, l, n)) low = mid;
			else high = mid - 1;
		}
		printf("%d\n", low);
	}
	return 0;
}
