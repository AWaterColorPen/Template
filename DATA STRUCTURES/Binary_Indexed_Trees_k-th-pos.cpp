#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define INF 200005

using namespace std;
int T_array[INF], Org[INF], inf;
int Find_pos(int n) // pos of n-th small number, or ,pos of n-th "1",
{
	int cnt=0, bit=0, bin=log2(n), i;
	for (i=bin; i>=0; i--)
		if (bit+=(1<<i), bit>inf || cnt+T_array[bit]>=n) bit-=(1<<i);
		else cnt+=T_array[bit];
	return bit+1;
}
int main()
{
	int i, j, n;
	for (i=1; i<INF; i++) Org[i]=1<<(n=log2(j));
	return 0;
}

