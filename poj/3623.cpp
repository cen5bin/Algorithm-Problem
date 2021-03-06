#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int maxn = 100010;
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
int rank[maxn], height[maxn];
void calheight(int *r,int *sa,int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++) rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
	for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}

int sa[maxn], r[maxn];

int main()
{
	int n;
	int count = 0;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++)
		{
			char c;
			scanf(" %c", &c);
			r[i] = c - 'A' + 1;
		}
		r[n] = 'Z' -'A' + 2;
		for (int i = n + 1; i <= 2 * n; i++)
			r[i] = r[2 * n - i];
		r[2 * n + 1] = 0;
		//for (int i = 0; i <= 2 * n + 1; i++) printf("%d ", r[i]);
		//puts("");
		da(r, sa, 2 * n + 2, 'Z' - 'A' + 3);
		calheight(r, sa, 2 * n + 1);
		//for (int i = 0; i <= 2 * n; i++)
		//	printf("%d ", rank[i]);
		int pre = 0, post = n+1;
		for (int i = 0; i < n; i++)
		{
			if (rank[pre] < rank[post])
				printf("%c", 'A' + r[pre++] - 1);
			else printf("%c", 'A' + r[post++] - 1);
			if (++count == 80)
			{
				puts("");
				count-=80;
			}
		}
		//puts("");
	}
	puts("");
	return 0;
}
