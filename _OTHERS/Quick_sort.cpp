#include <iostream>
#include <cstdio>
#define INF 2000005

using namespace std;
int Num[INF];
void Quick_sort(int l,int r)
{
	if (l>=r) return;
	int i=l, j=r, mid=Num[(r+l)/2];
	while (i<=j)
	{
		while (Num[i]<mid) i++;
		while (Num[j]>mid) j--;
		if (i<=j) swap(Num[i], Num[j]), i++, j--;
	}
	Quick_sort(l,j), Quick_sort(i,r);
}

