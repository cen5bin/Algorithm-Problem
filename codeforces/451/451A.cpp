#include <cstdio>
#include <cstring>

int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	int n,m;
	while (scanf("%d%d", &n, &m)==2)
	{
		if (min(m,n)%2)
			puts("Akshat");
		else 
			puts("Malvika");

	}
	return 0;
}
