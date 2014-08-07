#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>
#define MOD 1000000007
#define _int64 unsigned long long

using namespace std;
map <int, _int64> F;
_int64 Natrue_triangle(int n)
{
	if (F[n]!=0) return F[n];
	int i; _int64 cnt=0, res=0;
	for (cnt=0, i=1; i<=n/3; i++)
		cnt=(cnt+max((n-i)/2-max((n-2*i)/2+1, i)+1, 0))% MOD;
	for (i=2; i<=n/i; i++)
		if (n%i==0) {
				res=(res+Natrue_triangle(n/i))% MOD;
				if (n/i!=i)
				res=(res+Natrue_triangle(i))% MOD;
		}
	return F[n]=(cnt+MOD-res)%MOD, F[n];
}
