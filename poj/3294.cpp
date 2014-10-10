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
int xx[maxn];
char s[110][1010];
int ans[maxn], kk;
bool vis[110];
bool judge(int x, int l, int n)
{
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	bool yes = 0, add = 0, clear = 0;
	for (int i = 1; i <= l; i++)
	{
		if (height[i] < x)
		{
			memset(vis, 0, sizeof(vis));
			cnt = 0;
			add = 0;
			continue;
		}
		if (!vis[xx[sa[i-1]]]) vis[xx[sa[i-1]]] = 1, cnt++;
		if (!vis[xx[sa[i]]]) vis[xx[sa[i]]] = 1, cnt++;
		if (cnt >= n / 2 + 1 && !add)
		{
			add = 1;
			if (!clear) kk = 0, clear = 1;
			ans[kk++] = sa[i-1];
			yes = 1;
		}
	}
	return yes;
}

int main()
{
	int n;
	int cas = 0;
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++) scanf("%s", s[i]);
		int l = 0;
		int maxl = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; s[i][j]; j++)
				xx[l] = i, r[l++] = s[i][j] - 'a' + 1;
			r[l++] = 27 + i;
			maxl = MAX(maxl, strlen(s[i]));
		}
		r[l] = 0;
		da(r, sa, l+1, n+27);
		calheight(r, sa, l);
		int low = 0;
		int high = maxl;
		while (low < high)
		{
			int mid = (low + high + 1) >> 1;
			if (judge(mid, l, n)) low = mid;
			else high = mid - 1;
		}
		if (cas++) puts("");
		if (low == 0) puts("?");
		else 
		{
			for (int i = 0; i < kk; i++)
			{
				for (int j = ans[i]; j < ans[i] + low; j++) printf("%c", 'a'+r[j]-1);
				puts("");
			}
		}
		for (int i = 1; i <= l; i++)
		{

		}
	}
	return 0;
}
