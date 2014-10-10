#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int maxn = 120010;
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
const int MOD = 2012;
int sum[maxn], ff[maxn], tt[maxn], kk[maxn];
int main()
{
	kk[1] = 1;
	for (int i = 2; i < maxn; i++) kk[i] = (kk[i-1] * 10 + 1) % MOD;
	int n;
	while (scanf("%d", &n) == 1)
	{
		int l = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s);
			int l1 = strlen(s);
			bool yes = 0;
			int xxx = 0;
			for (int j = 0; j < l1; j++) 
			if (s[j] == '0' && !yes)
				continue;
			else 
			{
				xxx++;
				yes = 1;
				r[l++] = s[j] - '0' + 1;
			}
			l1 = xxx;
			ff[l-l1] = r[l-l1]-1;
			sum[l-l1] = ff[l-l1];
			for (int j = l-l1+1; j < l; j++) ff[j] = (ff[j-1]*10+(r[j]-1))%MOD, sum[j] = (sum[j-1] + ff[j])%MOD;
			for (int j = l - 1; j >= l - l1; j--) tt[j] = l - 1;
			tt[l] = -1;
			sum[l] = 0;
			r[l++] = 11 + i;
		}
		r[l] = 0;
		da(r, sa, l+1, 11+n);
		calheight(r, sa, l);
		int ans = 0;
		for (int i = 1; i <= l; i++)
		{
			if (tt[sa[i]] == -1) continue;
			if (r[sa[i]] == 1) continue;
			if (sa[i] == 0 || r[sa[i]-1] > 10)
			{
				ans = (ans + sum[tt[sa[i]]] - sum[sa[i]+height[i]-1] + MOD) % MOD;
				continue;
			}
			int l0 = tt[sa[i]] - (sa[i]+height[i]-1);
			int tmp0 = (kk[l0+height[i]+1] - kk[height[i]+1] + MOD) % MOD;
			ans = (ans + sum[tt[sa[i]]] - sum[sa[i]+height[i]-1] - ff[sa[i]-1]*tmp0 % MOD + MOD * 2) % MOD;
		}
		printf("%d\n", (ans % MOD + MOD) % MOD);
	}
	return 0;
}
