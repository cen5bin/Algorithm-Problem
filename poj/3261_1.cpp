#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
const int maxn = 1000010;
int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
int c0(int *r,int a,int b) {return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}
int c12(int k,int *r,int a,int b) 
{
  if(k==2) return r[a]<r[b]||(r[a]==r[b]&&c12(1,r,a+1,b+1));
  else return r[a]<r[b]||(r[a]==r[b]&&wv[a+1]<wv[b+1]);
}
void sort0(int *r,int *a,int *b,int n,int m)
{
     int i;
     for(i=0;i<n;i++) wv[i]=r[a[i]];
     for(i=0;i<m;i++) ws[i]=0;
     for(i=0;i<n;i++) ws[wv[i]]++;
     for(i=1;i<m;i++) ws[i]+=ws[i-1];
     for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
     return;
}
void dc3(int *r,int *sa,int n,int m)
{
  int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
  r[n]=r[n+1]=0;
  for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
  sort0(r+2,wa,wb,tbc,m);
  sort0(r+1,wb,wa,tbc,m);
  sort0(r,wa,wb,tbc,m);
  for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
  rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
  if(p<tbc) dc3(rn,san,tbc,p);
  else for(i=0;i<tbc;i++) san[rn[i]]=i;
  for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
  if(n%3==1) wb[ta++]=n-1;
  sort0(r,wb,wa,ta,m);
  for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
  for(i=0,j=0,p=0;i<ta && j<tbc;p++)
  sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
  for(;i<ta;p++) sa[p]=wa[i++];
  for(;j<tbc;p++) sa[p]=wb[j++];
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

int sa[maxn*3], r[maxn*3];

//下面这个函数不是模板的内容
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
          r[n] = 0; //末尾补0
          dc3(r, sa, n+1, m+1); //调用da必须是用n+1
          calheight(r, sa, n); //计算height只要用n就好
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
