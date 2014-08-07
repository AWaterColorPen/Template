#include <iostream>
#include <cstdio>
#define INF 0x20001
#define _int64 long long

using namespace std;
_int64 S_org[INF], T_deli[INF], T_del[INF], inf;
void Update0(int i, int m, _int64 *t)
{
	for (; i<=inf; i+=i&(-i)) t[i]+=m;
}
void Update(int i, int j, int m)
{
	Update0(i, m*i, T_deli),	Update0(j+1, -m*(j+1), T_deli),
	Update0(i, m, T_del),		Update0(j+1, -m, T_del);
}
_int64 Sum(int n)
{
	_int64 sum=S_org[n], k=n+1, now;
	for (now=0; n; n-=n&(-n))
		sum-=T_deli[n], now+=T_del[n];
	return sum+=k*now;
}
int main()
{
	int i,j,m,n;
	for (i=1, scanf("%d%d", &n, &m); i<=n; i++)
		scanf("%d", &j), S_org[i]=S_org[i-1]+j;
	return 0;
}
